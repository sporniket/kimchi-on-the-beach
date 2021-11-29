#ifndef CONTROL_PANEL_ESP32_HPP
#define CONTROL_PANEL_ESP32_HPP

// standard includes
#include <cstdint>

// esp32 includes

// project includes
#include "sdkconfig.h"
#include "FeedbackLed.hpp"
#include "Task.h"
#include "GeneralPurposeInputOutput.hpp"
#include "InputButton.hpp"

/** @brief The control panel implementation for the ESP 32.
 */
class ControlPanelEsp32 {
    private:
        FeedbackLed mainLed ;
        InputButton actionWhite = InputButton(CONFIG_PIN_BUTTON_ACTION_WHITE) ;
        Task* ledsUpdater ;
        Task* buttonWatcher ;
        GeneralPurposeInputOutput* gpio ;

    public:
        ControlPanelEsp32(GeneralPurposeInputOutput* gpioImpl) ;
        virtual ~ControlPanelEsp32() ;
        void start() ;
        inline FeedbackLed* getMainLed() {return &mainLed; }
        inline InputButton* getActionWhite() {return &actionWhite; }
        inline GeneralPurposeInputOutput* getGpio() {return gpio ;}
} ;

#endif