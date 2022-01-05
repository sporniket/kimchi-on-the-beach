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

#ifndef INPUT_BUTTON_HPP
#define INPUT_BUTTON_HPP

// standard includes
#include <cstdint>

// esp32 includes

// project includes
#include "GeneralPurposeInputOutput.hpp"

/**
 * @brief Specification of the debouncing filter.
 * 
 * The typical debouncer read a digital signal, and insert at the right of the previous reads ;
 * it keeps only a given number of read. When the signal is stable for the given width - 1, the 
 * value of the signal is considered changed. The higher the number of read kept, the slower the
 * debouncing is.
 */
typedef struct {
    uint16_t mask;
    uint16_t pattern;
} DebounceSpecification ;

typedef enum {
    DEBOUNCER_MINIMAL = 0b000000001111 ,
    DEBOUNCER_TYPICAL = 0b000011111111 ,
    DEBOUNCER_HEAVY = 0b111111111111,
} Debouncer ;

typedef enum {
    LOW,
    EDGE_HIGH,
    HIGH,
    EDGE_LOW
} InputButtonState ;

class InputButton ; //forward declaration for event framework

/**
 * @brief The types of events form an input button.
 * @see InputButtonEvent.
 */
typedef enum {
    STATE_CHANGE
} InputButtonEventType ;

/**
 * @brief A description of an event from an input button.
 * @see InputButtonListener.
 */
typedef struct {
    InputButtonEventType type;
    InputButton* source ;
} InputButtonEvent ;

/**
 * @brief Interface for being notified of input button events.
 */
class InputButtonListener {
    public:
        virtual ~InputButtonListener() ;
        virtual void onInputButtonEvent(InputButtonEvent* event) = 0;
} ;

/** @brief Model of a debounced input button.
 * 
 * To use this model, read a gpio and provide this state to the `update()` methode. The button will 
 * debounce the received signal and update its state.
 * 
 * A button has one listener (TODO : support any number of listeners) that can react to a button state change.
 */
class InputButton {
    private:
        uint64_t id;
        uint16_t debounceMask ;
        uint16_t debouncePatternHigh ;
        uint16_t debouncePatternLow ;
        uint16_t history = 0;
        InputButtonState state = LOW;
        InputButtonListener* listener ;

    public:
        InputButton(uint64_t idValue) ;
        virtual ~InputButton() ;
        inline InputButton* withDebouncer(Debouncer debouncer) {
            debounceMask = (uint16_t)debouncer;
            debouncePatternHigh = debounceMask >> 1 ;
            debouncePatternLow = (~debouncePatternHigh) & debounceMask ;
            return this ;
        }
        inline InputButton* withListener(InputButtonListener* listenerImpl) {
            listener = listenerImpl ;
            return this ;
        }

        /**
         * @brief Get the Id of the button.
         * 
         * @return uint the id value.
         */
        inline uint64_t getId() {return id ;}
        /**
         * @brief Get the current state of the button.
         * 
         * @return InputButtonState the state. 
         */
        inline InputButtonState getCurrentState() {return state;}

        /**
         * @brief Assert whether the button is "high" (pressed).
         * 
         * @return true when it is pressed.
         * @return false when it is not pressed.
         */
        inline bool isHigh() {return (EDGE_HIGH == state) || (HIGH == state) ;}

        /**
         * @brief Assert whether the button state has just changed.
         * 
         * @return true when the state has just changed.
         * @return false when there is no change.
         */
        inline bool isTransient() {return (EDGE_HIGH == state) || (EDGE_LOW == state) ;}

        /**
         * @brief Update the state according to the new reading of the input. 
         * 
         * @param state the latest reading from a gpio.
         * @return InputButtonState the current state.
         */
        InputButtonState update(bool state) ;


} ;

#endif