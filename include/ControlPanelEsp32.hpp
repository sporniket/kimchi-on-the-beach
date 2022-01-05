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
        InputButton leftYellow = InputButton(CONFIG_PIN_BUTTON_LEFT_YELLOW);
        InputButton downGreen = InputButton(CONFIG_PIN_BUTTON_DOWN_GREEN);
        InputButton upBlue = InputButton(CONFIG_PIN_BUTTON_UP_BLUE);
        InputButton rightRed = InputButton(CONFIG_PIN_BUTTON_RIGHT_RED);
        Task* ledsUpdater ;
        Task* buttonWatcher ;
        GeneralPurposeInputOutput* gpio ;

    public:
        ControlPanelEsp32(GeneralPurposeInputOutput* gpioImpl) ;
        virtual ~ControlPanelEsp32() ;
        void start() ;
        inline FeedbackLed* getMainLed() {return &mainLed; }
        inline InputButton* getActionWhite() {return &actionWhite; }
        inline InputButton* getLeftYellow() {return &leftYellow; }
        inline InputButton* getDownGreen() {return &downGreen; }
        inline InputButton* getUpBlue() {return &upBlue; }
        inline InputButton* getRightRed() {return &rightRed; }
        inline GeneralPurposeInputOutput* getGpio() {return gpio ;}
} ;

#endif