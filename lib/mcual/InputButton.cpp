
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