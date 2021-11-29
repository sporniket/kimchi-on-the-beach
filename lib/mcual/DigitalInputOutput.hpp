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