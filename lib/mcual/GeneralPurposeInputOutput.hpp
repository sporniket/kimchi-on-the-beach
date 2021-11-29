#ifndef GENERAL_PURPOSE_INPUT_OUTPUT_HPP
#define GENERAL_PURPOSE_INPUT_OUTPUT_HPP

// standard includes
#include <cstdint>

// esp32 includes

// project includes
#include "TypesForInputOutput.hpp"
#include "DigitalInputOutput.hpp"

/** @brief What the class is for.
 */
class GeneralPurposeInputOutput {
    private:
        DigitalInputOutput* digital ;

    public:
        virtual ~GeneralPurposeInputOutput() {}
        inline DigitalInputOutput* getDigital() { return digital; }
        inline GeneralPurposeInputOutput* withDigital(DigitalInputOutput* dio) {digital = dio ; return this ;}
} ;

#endif