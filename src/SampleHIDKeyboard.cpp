// Original file from https://github.com/nkolban/esp32-snippets/
// Editions of this file are copyright 2021,2022 David SPORN
// ---
// This file is part of 'Kimchi on the beach'.
// ---
// 'Kimchi on the beach' is free software: you can redistribute it and/or 
// modify it under the terms of the GNU General Public License as published 
// by the Free Software Foundation, either version 3 of the License, or 
// (at your option) any later version.

// 'Kimchi on the beach' is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
// Public License for more details.

// You should have received a copy of the GNU General Public License along 
// with 'Kimchi on the beach'. If not, see <https://www.gnu.org/licenses/>. 

/**
 * Create a new BLE server.
 */
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "BLE2902.h"
#include "BLEHIDDevice.h"
#include "HIDKeyboardTypes.h"
#include <esp_log.h>
#include <string>
#include <Task.h>

#include "sdkconfig.h"
#include "ControlPanelEsp32.hpp"
#include "InputButton.hpp"
#include "HidBootKeyboardInputReport.hpp"
#include "KimchiOnTheBeach.hpp"
#include "ReportMapProvider.hpp"

static char LOG_TAG[] = "SampleHIDDevice";

static BLEHIDDevice* hid;
BLECharacteristic* input;
BLECharacteristic* output;

/*
 * This callback is connect with output report. In keyboard output report report special keys changes, like CAPSLOCK, NUMLOCK
 * We can add digital pins with LED to show status
 * bit 1 - NUM LOCK
 * bit 2 - CAPS LOCK
 * bit 3 - SCROLL LOCK
 */
class MyOutputCallbacks : public BLECharacteristicCallbacks {
	void onWrite(BLECharacteristic* me){
		uint8_t* value = (uint8_t*)(me->getValue().c_str());
		ESP_LOGI(LOG_TAG, "special keys: %d", *value);
	}
};

class MyTask : public Task, public InputButtonListener, public HidBootKeyboardInputReportListener {
	HidBootKeyboardInputReport report ;
	void run(void*){
		//vTaskDelay(5000/portTICK_PERIOD_MS);  // wait 5 seconds before send first message
		while(1){
			//const char* hello = "Hello world from esp32 hid keyboard!!!\n";
			//while(*hello){
				//KEYMAP map = keymap[(uint8_t)*hello];
				/*
				 * simulate keydown, we can send up to 6 keys
				 */
				//uint8_t a[] = {map.modifier, 0x0, map.usage, 0x0,0x0,0x0,0x0,0x0};
				//input->setValue(a,sizeof(a));
				//input->notify();

				/*
				 * simulate keyup
				 */
				//uint8_t v[] = {0x0, 0x0, 0x0, 0x0,0x0,0x0,0x0,0x0};
				//input->setValue(v, sizeof(v));
				//input->notify();
				//hello++;

				//vTaskDelay(10/portTICK_PERIOD_MS);
			//}
			//ESP_LOGI(LOG_TAG, "I'm alive and well !");
			vTaskDelay(2000/portTICK_PERIOD_MS); // simulate write message every 2 seconds
		}
	}

	public:
	MyTask() {
		report.withListener(this) ;
	}
	void onInputButtonEvent(InputButtonEvent* event) {
		if (!isStarted()) return; // no connection
		if (STATE_CHANGE == event->type) {
			switch (event->source->getId()) {
				case CONFIG_PIN_BUTTON_ACTION_WHITE:
					if (event->source->isHigh()) {
						ESP_LOGI(LOG_TAG, "send key press action");
						report.registerKeyPress(0x0b) ;
					} else {
						ESP_LOGI(LOG_TAG, "send key release action");
						report.registerKeyRelease(0x0b) ;
					}
				break;
			}
		}
	}

	void onHidBootKeyboardInputReportEvent(HidBootKeyboardInputReportEvent* event) {
		if (!isStarted()) return; // no connection
		if (REPORT_CHANGED == event->type) {
			ESP_LOGI(LOG_TAG, "send new report");
			input->setValue(event->source->getReport(), event->source->getSizeOfReport()) ;
			input->notify() ;
		}
	}
};

MyTask *task;
class MyCallbacks : public BLEServerCallbacks {
	private:
		KimchiOnTheBeach kotb;
		bool useKotb = true ;
	public:
	ControlPanelEsp32* controlPanel ;
	KimchiOnTheBeach* getKimchiOnTheBeach() {return &kotb ;}
	void onConnect(BLEServer* pServer){
		controlPanel->getMainLed()->setFeedbackSequenceAndLoop(ON) ;
		if(!useKotb) {
			task->start(); 
		} else {
			kotb.start();
		}
	}

	void onDisconnect(BLEServer* pServer){
		controlPanel->getMainLed()->setFeedbackSequenceAndLoop(BLINK_TWICE);
		if(!useKotb) {
			task->stop(); 
		} else {
			kotb.stop();
		}
	}
};

class MainBLEServer: public Task {
	public:
	ControlPanelEsp32* controlPanel ;
	void run(void *data) {
		ESP_LOGD(LOG_TAG, "Starting BLE work!");
		controlPanel->getMainLed()->setFeedbackSequenceAndLoop(BLINK_TWICE);

		task = new MyTask();
		BLEDevice::init(CONFIG_LABEL_DEVICE_NAME);
		BLEServer *pServer = BLEDevice::createServer();
		MyCallbacks *callbacks = new MyCallbacks();
		callbacks->controlPanel = controlPanel;
		//controlPanel->getActionWhite()->withListener(task) ;
		controlPanel->getActionWhite()->withListener(callbacks->getKimchiOnTheBeach()) ;
		controlPanel->getLeftYellow()->withListener(callbacks->getKimchiOnTheBeach()) ;
		controlPanel->getDownGreen()->withListener(callbacks->getKimchiOnTheBeach()) ;
		controlPanel->getUpBlue()->withListener(callbacks->getKimchiOnTheBeach()) ;
		controlPanel->getRightRed()->withListener(callbacks->getKimchiOnTheBeach()) ;
		pServer->setCallbacks(callbacks);

		/*
		 * Instantiate hid device
		 */
		hid = new BLEHIDDevice(pServer);


		//input = hid->inputReport(1); // <-- input REPORTID from report map
		callbacks->getKimchiOnTheBeach()->withBleHidDevice(hid) ;
		output = hid->outputReport(1); // <-- output REPORTID from report map

		output->setCallbacks(new MyOutputCallbacks());

		/*
		 * Set manufacturer name (OPTIONAL)
		 * https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.manufacturer_name_string.xml
		 */
		std::string name = CONFIG_LABEL_MANUFACTURER_NAME;
		hid->manufacturer()->setValue(name);

		/*
		 * Set pnp parameters (MANDATORY)
		 * https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.pnp_id.xml
		 */

		hid->pnp(0x02, 0xe502, 0xa111, 0x0210);

		/*
		 * Set hid informations (MANDATORY)
		 * https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.hid_information.xml
		 */
		hid->hidInfo(0x00,0x01);


		/*
		 * Keyboard
		 */
		const uint8_t reportMap[] = {
			USAGE_PAGE(1),      0x01,       // Generic Desktop Ctrls
			USAGE(1),           0x06,       // Keyboard
			COLLECTION(1),      0x01,       // Application
			REPORT_ID(1),		0x01,		// REPORTID
			USAGE_PAGE(1),      0x07,       //   Kbrd/Keypad
			USAGE_MINIMUM(1),   0xE0,
			USAGE_MAXIMUM(1),   0xE7,
			LOGICAL_MINIMUM(1), 0x00,
			LOGICAL_MAXIMUM(1), 0x01,
			REPORT_SIZE(1),     0x01,       //   1 byte (Modifier)
			REPORT_COUNT(1),    0x08,
			INPUT(1),           0x02,       //   Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position
			REPORT_COUNT(1),    0x01,       //   1 byte (Reserved)
			REPORT_SIZE(1),     0x08,
			INPUT(1),           0x01,       //   Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position
			REPORT_COUNT(1),    0x05,       //   5 bits (Num lock, Caps lock, Scroll lock, Compose, Kana)
			REPORT_SIZE(1),     0x01,
			USAGE_PAGE(1),      0x08,       //   LEDs
			USAGE_MINIMUM(1),   0x01,       //   Num Lock
			USAGE_MAXIMUM(1),   0x05,       //   Kana
			OUTPUT(1),          0x02,       //   Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile
			REPORT_COUNT(1),    0x01,       //   3 bits (Padding)
			REPORT_SIZE(1),     0x03,
			OUTPUT(1),          0x01,       //   Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile
			REPORT_COUNT(1),    0x06,       //   6 bytes (Keys)
			REPORT_SIZE(1),     0x08,
			LOGICAL_MINIMUM(1), 0x00,
			LOGICAL_MAXIMUM(1), 0x65,       //   101 keys
			USAGE_PAGE(1),      0x07,       //   Kbrd/Keypad
			USAGE_MINIMUM(1),   0x00,
			USAGE_MAXIMUM(1),   0x65,
			INPUT(1),           0x00,       //   Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position
			END_COLLECTION(0)
		};
		/*
		 * Set report map (here is initialized device driver on client side) (MANDATORY)
		 * https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.report_map.xml
		 */
		ReportMapDescriptor *kimchiReportMap = ReportMapProvider::getReportMapForCombinedKeyboardMouseGamepadGamepad() ;
		hid->reportMap(kimchiReportMap->data, kimchiReportMap->size);
		//hid->reportMap((uint8_t*)reportMap, sizeof(reportMap));

		/*
		 * We are prepared to start hid device services. Before this point we can change all values and/or set parameters we need.
		 * Also before we start, if we want to provide battery info, we need to prepare battery service.
		 * We can setup characteristics authorization
		 */
		hid->startServices();

		/*
		 * Its good to setup advertising by providing appearance and advertised service. This will let clients find our device by type
		 */
		BLEAdvertising *pAdvertising = pServer->getAdvertising();
		pAdvertising->setAppearance(HID_KEYBOARD);
		pAdvertising->addServiceUUID(hid->hidService()->getUUID());
		pAdvertising->start();


		BLESecurity *pSecurity = new BLESecurity();
		pSecurity->setAuthenticationMode(ESP_LE_AUTH_BOND);

		ESP_LOGD(LOG_TAG, "Advertising started!");
		delay(1000000);
	}
};


void SampleHID(ControlPanelEsp32* controlPanel)
{
	//esp_log_level_set("*", ESP_LOG_DEBUG);
	MainBLEServer* pMainBleServer = new MainBLEServer();
	pMainBleServer->controlPanel = controlPanel ;
	pMainBleServer->setStackSize(20000);
	pMainBleServer->start();

} // app_main
