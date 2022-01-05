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
#include "InputButton.hpp"

InputButton::~InputButton(){}
InputButtonListener::~InputButtonListener(){}
// write code here...

InputButton::InputButton(uint64_t idValue) : id(idValue) {}

InputButtonState InputButton::update(bool newState) {
            history = history << 1;
            if (newState) ++history ;
            history = history & debounceMask ;
            switch (state)
            {
            case LOW:
                if (history == debouncePatternHigh) {state = EDGE_HIGH ;}
                break;
            case EDGE_HIGH:
                state = HIGH;
                break;
            case HIGH:
                if (history == debouncePatternLow) {state = EDGE_LOW;}
                break;
            case EDGE_LOW:
                state = LOW ;
                break;
            default:
                break;
            }
            if(isTransient() && nullptr != listener) {
                InputButtonEvent event = {.type = STATE_CHANGE, .source = this} ;
                listener->onInputButtonEvent(&event) ;
            }
            return state;
        }