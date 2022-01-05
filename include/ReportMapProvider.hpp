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