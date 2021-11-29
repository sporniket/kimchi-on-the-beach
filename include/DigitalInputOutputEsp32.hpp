#ifndef DIGITAL_INPUT_OUTPUT_ESP32_HPP
#define DIGITAL_INPUT_OUTPUT_ESP32_HPP

// standard includes
#include <cstdint>

// esp32 includes
#include "driver/gpio.h"

// project includes
#include "TypesForInputOutput.hpp"
#include "DigitalInputOutput.hpp"

/** @brief What the class is for.
 */
class DigitalInputOutputEsp32 : public DigitalInputOutput{
    private:

    public:
        virtual ~DigitalInputOutputEsp32() ;
        /**
         * @brief Prepare the specified pin to be read from or to be written to.
         */
        inline virtual void setup(uint8_t pin, PinDirection direction ) {
            gpio_pad_select_gpio(pin);
            gpio_set_direction(gpio_num_t(pin), READ == direction ? GPIO_MODE_INPUT : GPIO_MODE_OUTPUT);
        }
        /**
         * @brief Get the value from the specified IO pin.
         */
        inline virtual bool read(uint8_t pin) {
            return 0 != gpio_get_level(gpio_num_t(pin));
        }
        /** 
         * @brief Set the value of the specified IO pin.
         */
        inline virtual void write (uint8_t pin, bool value) {
            gpio_set_level(gpio_num_t(pin), (value) ? 1 : 0);
        }

} ;

#endif