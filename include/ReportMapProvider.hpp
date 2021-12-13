#ifndef REPORT_MAP_PROVIDER_HPP
#define REPORT_MAP_PROVIDER_HPP

// standard includes
#include <cstdint>

// esp32 includes

// project includes
#include "HIDTypes.h"

typedef struct {
    uint8_t* data ;
    uint32_t size ;
} ReportMapDescriptor ;

/** @brief What the class is for.
 */
class ReportMapProvider {
    private:

    public:
        virtual ~ReportMapProvider() ;
        /**
         * @brief Get the HID Report Map For a simple keyboard device.
         * 
         * @return ReportMapDescriptor 
         */
        static ReportMapDescriptor * getReportMapForSimpleKeyboard() ;
        /**
         * @brief Get the HID Report Map For a combined keyboard, mouse and two gamepads.
         * 
         * @return ReportMapDescriptor 
         */
        static ReportMapDescriptor * getReportMapForCombinedKeyboardMouseGamepadGamepad() ;

} ;

#endif