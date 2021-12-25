
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
                    reportOfMouse.moveCursor(-8,0)->notify() ;
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
                    reportOfMouse.moveCursor(8,0)->notify() ;
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
    if (REPORT_CHANGED == event->type) {
        input->setValue(event->source->getReport(), event->source->getSizeOfReport()) ;
        input->notify() ;
        ESP_LOGI(LOG_TAG, "done notify channel %d", KimchiInputChannel::CHANNEL_KEYBOARD);
    }
}

void KimchiOnTheBeach::onHidBootMouseInputReportEvent(HidBootMouseInputReportEvent* event) {
    ESP_LOGI(LOG_TAG, "--->onHidBootMouseInputReportEvent");
    if (!isStarted()) return; // no connection
    ESP_LOGI(LOG_TAG, "is started, event_type: %d", event->type);
    BLECharacteristic* input = inputChannel[KimchiInputChannel::CHANNEL_MOUSE] ;
    if (REPORT_CHANGED_FOR_MOUSE == event->type) {
        input->setValue(event->source->getReport(), event->source->getSizeOfReport()) ;
        input->notify() ;
        ESP_LOGI(LOG_TAG, "done notify channel %d", KimchiInputChannel::CHANNEL_MOUSE);
    }
}
