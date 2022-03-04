// Copyright 2021,2022 David SPORN
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

// header include
#include "KimchiOnTheBeach.hpp"

static char LOG_TAG[] = "KimchiOnTheBeach";


KimchiOnTheBeach::~KimchiOnTheBeach(){}
// write code here...

KimchiOnTheBeach::KimchiOnTheBeach(){
    reportOfKeyboard.withListener(this) ;
    reportOfMouse.withListener(this) ;
}

// event handlers
void KimchiOnTheBeach::onInputButtonEvent(InputButtonEvent* event) {
    ESP_LOGI(LOG_TAG, "--->onInputButtonEvent");
    if (!isStarted()) return; // no connection
    ESP_LOGI(LOG_TAG, "is started, event_type: %d - transient : %d - high %d", event->type, event->source->isTransient(), event->source->isHigh());
    if (STATE_CHANGE == event->type && event->source->isTransient()) {
        switch (event->source->getId()) {
            case CONFIG_PIN_BUTTON_ACTION_WHITE:
                ESP_LOGI(LOG_TAG, "from action white");
                if (event->source->isHigh()) {
                    reportOfKeyboard.registerKeyPress(0x0b) ;
                } else {
                    reportOfKeyboard.registerKeyRelease(0x0b) ;
                }
            break;
            case CONFIG_PIN_BUTTON_LEFT_YELLOW:
                ESP_LOGI(LOG_TAG, "from left yellow");
                if (event->source->isHigh()) {
                    //reportOfKeyboard.registerKeyPress(0x0c) ;
                    reportOfMouse.moveCursor(-16,-16)->notify() ;
                } else {
                    //reportOfKeyboard.registerKeyRelease(0x0c) ;
                }
            break;
            case CONFIG_PIN_BUTTON_DOWN_GREEN:
                ESP_LOGI(LOG_TAG, "from down green");
                if (event->source->isHigh()) {
                    reportOfKeyboard.registerKeyPress(0x0d) ;
                } else {
                    reportOfKeyboard.registerKeyRelease(0x0d) ;
                }
            break;
            case CONFIG_PIN_BUTTON_UP_BLUE:
                ESP_LOGI(LOG_TAG, "from up blue");
                if (event->source->isHigh()) {
                    reportOfKeyboard.registerKeyPress(0x0e) ;
                } else {
                    reportOfKeyboard.registerKeyRelease(0x0e) ;
                }
            break;
            case CONFIG_PIN_BUTTON_RIGHT_RED:
                ESP_LOGI(LOG_TAG, "from right red");
                if (event->source->isHigh()) {
                    //reportOfKeyboard.registerKeyPress(0x0f) ;
                    reportOfMouse.moveCursor(16,16)->notify() ;
                } else {
                    //reportOfKeyboard.registerKeyRelease(0x0f) ;
                }
        }
    }
}

void KimchiOnTheBeach::onHidBootKeyboardInputReportEvent(HidBootKeyboardInputReportEvent* event) {
    ESP_LOGI(LOG_TAG, "--->onHidBootKeyboardInputReportEvent");
    if (!isStarted()) return; // no connection
    ESP_LOGI(LOG_TAG, "is started, event_type: %d", event->type);
    BLECharacteristic* input = inputChannel[KimchiInputChannel::CHANNEL_KEYBOARD] ;
//    forceNotifyAndIndicate((BLE2902*)(input->getDescriptorByUUID((uint16_t)0x2902)));
    if (REPORT_CHANGED == event->type) {
        input->setValue(event->source->getReport(), event->source->getSizeOfReport()) ;
        input->notify(true) ;
        ESP_LOGI(LOG_TAG, "done notify channel %d", KimchiInputChannel::CHANNEL_KEYBOARD);
    }
}

void KimchiOnTheBeach::onHidBootMouseInputReportEvent(HidBootMouseInputReportEvent* event) {
    ESP_LOGI(LOG_TAG, "--->onHidBootMouseInputReportEvent");
    if (!isStarted()) return; // no connection
    ESP_LOGI(LOG_TAG, "is started, event_type: %d", event->type);
    BLECharacteristic* input = inputChannel[KimchiInputChannel::CHANNEL_MOUSE] ;
//    forceNotifyAndIndicate((BLE2902*)(input->getDescriptorByUUID((uint16_t)0x2902)));
    if (REPORT_CHANGED_FOR_MOUSE == event->type) {
        input->setValue(event->source->getReport(), event->source->getSizeOfReport()) ;
        input->notify(true) ;
        ESP_LOGI(LOG_TAG, "done notify channel %d", KimchiInputChannel::CHANNEL_MOUSE);
    }
}

void KimchiOnTheBeach::forceNotifyAndIndicate(BLE2902* p2902) {
//    if(!p2902->getNotifications()) {
//        p2902->setNotifications(true) ;
//        ESP_LOGI("KimchiOnTheBeach","force notification of channel") ;
//    }
//    if(!p2902->getIndications()) {
//        p2902->setIndications(true) ;
//        ESP_LOGI("KimchiOnTheBeach","force indication of channelt") ;
//    }
}