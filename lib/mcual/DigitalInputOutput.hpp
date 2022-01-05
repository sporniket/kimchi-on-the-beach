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

#ifndef DIGITAL_INPUT_OUTPUT_HPP
#define DIGITAL_INPUT_OUTPUT_HPP

// standard includes
#include <cstdint>

// esp32 includes

// project includes
#include "TypesForInputOutput.hpp"

/** @brief Model of the digital IO system.
 */
class DigitalInputOutput {
    private:

    public:
        virtual ~DigitalInputOutput() ;
        /**
         * @brief Prepare the specified pin to be read from or to be written to.
         */
        virtual void setup(uint8_t pin, PinDirection direction ) = 0 ;
        /**
         * @brief Get the value from the specified IO pin.
         */
        virtual bool read(uint8_t pin) = 0 ;
        /** 
         * @brief Set the value of the specified IO pin.
         */
        virtual void write (uint8_t pin, bool value) = 0;
        /**
         * @brief Macro to set the pin to high.
         */
        inline void setToHigh(uint8_t pin) {write(pin, true);}
        /**
         * @brief Macro to set the pin to low.
         */
        inline void setToLow(uint8_t pin) {write(pin, false);}
} ;

#endif