
// header include
#include "ReportMapProvider.hpp"

ReportMapProvider::~ReportMapProvider(){}
// write code here...

/**
 * Report map of a single keyboard.
 */
const uint8_t reportMapKeyboard[] = {
    USAGE_PAGE(1),      0x01,       // Generic Desktop Ctrls
    USAGE(1),           0x06,       // Keyboard
    COLLECTION(1),      0x01,       // Application
    REPORT_ID(1),		0x01,		// REPORTID
    USAGE_PAGE(1),      0x07,       //   Kbrd/Keypad
    USAGE_MINIMUM(1),   0xE0,
    USAGE_MAXIMUM(1),   0xE7,
    LOGICAL_MINIMUM(1), 0x00,
    LOGICAL_MAXIMUM(1), 0x01,
    REPORT_SIZE(1),     0x01,       //   1 byte (Modifier)
    REPORT_COUNT(1),    0x08,
    INPUT(1),           0x02,       //   Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position
    REPORT_COUNT(1),    0x01,       //   1 byte (Reserved)
    REPORT_SIZE(1),     0x08,
    INPUT(1),           0x01,       //   Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position
    REPORT_COUNT(1),    0x05,       //   5 bits (Num lock, Caps lock, Scroll lock, Compose, Kana)
    REPORT_SIZE(1),     0x01,
    USAGE_PAGE(1),      0x08,       //   LEDs
    USAGE_MINIMUM(1),   0x01,       //   Num Lock
    USAGE_MAXIMUM(1),   0x05,       //   Kana
    OUTPUT(1),          0x02,       //   Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile
    REPORT_COUNT(1),    0x01,       //   3 bits (Padding)
    REPORT_SIZE(1),     0x03,
    OUTPUT(1),          0x01,       //   Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile
    REPORT_COUNT(1),    0x06,       //   6 bytes (Keys)
    REPORT_SIZE(1),     0x08,
    LOGICAL_MINIMUM(1), 0x00,
    LOGICAL_MAXIMUM(1), 0x65,       //   101 keys
    USAGE_PAGE(1),      0x07,       //   Kbrd/Keypad
    USAGE_MINIMUM(1),   0x00,
    USAGE_MAXIMUM(1),   0x65,
    INPUT(1),           0x00,       //   Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position
    END_COLLECTION(0)
};
/**
 * Report map of a single keyboard.
 */
const uint8_t reportMapCombinedKeyboardMouseGamepadGamepad[] = {
    // ========================<[ KEYBOARD  ]>========================
    // source : https://github.com/nkolban/esp32-snippets
    USAGE_PAGE(1),      0x01,       // Generic Desktop Ctrls
    USAGE(1),           0x06,       // Keyboard
    COLLECTION(1),      0x01,       // Application
    REPORT_ID(1),		0x01,		// REPORTID #1 (first device)
    USAGE_PAGE(1),      0x07,       //   Kbrd/Keypad
    USAGE_MINIMUM(1),   0xE0,
    USAGE_MAXIMUM(1),   0xE7,
    LOGICAL_MINIMUM(1), 0x00,
    LOGICAL_MAXIMUM(1), 0x01,
    REPORT_SIZE(1),     0x01,       //   1 byte (Modifier)
    REPORT_COUNT(1),    0x08,
    INPUT(1),           0x02,       //   Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position
    REPORT_COUNT(1),    0x01,       //   1 byte (Reserved)
    REPORT_SIZE(1),     0x08,
    INPUT(1),           0x01,       //   Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position
    REPORT_COUNT(1),    0x05,       //   5 bits (Num lock, Caps lock, Scroll lock, Compose, Kana)
    REPORT_SIZE(1),     0x01,
    USAGE_PAGE(1),      0x08,       //   LEDs
    USAGE_MINIMUM(1),   0x01,       //   Num Lock
    USAGE_MAXIMUM(1),   0x05,       //   Kana
    OUTPUT(1),          0x02,       //   Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile
    REPORT_COUNT(1),    0x01,       //   3 bits (Padding)
    REPORT_SIZE(1),     0x03,
    OUTPUT(1),          0x01,       //   Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile
    REPORT_COUNT(1),    0x06,       //   6 bytes (Keys)
    REPORT_SIZE(1),     0x08,
    LOGICAL_MINIMUM(1), 0x00,
    LOGICAL_MAXIMUM(1), 0x65,       //   101 keys
    USAGE_PAGE(1),      0x07,       //   Kbrd/Keypad
    USAGE_MINIMUM(1),   0x00,
    USAGE_MAXIMUM(1),   0x65,
    INPUT(1),           0x00,       //   Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position
    END_COLLECTION(0),
    // ========================<[ MOUSE     ]>========================
    // source : https://github.com/T-vK/ESP32-BLE-Mouse
    USAGE_PAGE(1),      0x01, // USAGE_PAGE (Generic Desktop)
    USAGE(1),           0x02, // USAGE (Mouse)
    COLLECTION(1),      0x01, // COLLECTION (Application)
    REPORT_ID(1),		0x02, //   REPORTID #2
    USAGE(1),           0x01, //   USAGE (Pointer)
    COLLECTION(1),      0x00, //   COLLECTION (Physical)
    // ------------------------------------------------- Buttons (Left, Right, Middle, Back, Forward)
    USAGE_PAGE(1),      0x09, //     USAGE_PAGE (Button)
    USAGE_MINIMUM(1),   0x01, //     USAGE_MINIMUM (Button 1)
    USAGE_MAXIMUM(1),   0x05, //     USAGE_MAXIMUM (Button 5)
    LOGICAL_MINIMUM(1), 0x00, //     LOGICAL_MINIMUM (0)
    LOGICAL_MAXIMUM(1), 0x01, //     LOGICAL_MAXIMUM (1)
    REPORT_SIZE(1),     0x01, //     REPORT_SIZE (1)
    REPORT_COUNT(1),    0x05, //     REPORT_COUNT (5)
    INPUT(1),           0x02, //     INPUT (Data, Variable, Absolute) ;5 button bits
    // ------------------------------------------------- Padding
    REPORT_SIZE(1),     0x03, //     REPORT_SIZE (3)
    REPORT_COUNT(1),    0x01, //     REPORT_COUNT (1)
    INPUT(1),           0x03, //     INPUT (Constant, Variable, Absolute) ;3 bit padding
    // ------------------------------------------------- X/Y position, Wheel
    USAGE_PAGE(1),      0x01, //     USAGE_PAGE (Generic Desktop)
    USAGE(1),           0x30, //     USAGE (X)
    USAGE(1),           0x31, //     USAGE (Y)
    USAGE(1),           0x38, //     USAGE (Wheel)
    LOGICAL_MINIMUM(1), 0x81, //     LOGICAL_MINIMUM (-127)
    LOGICAL_MAXIMUM(1), 0x7f, //     LOGICAL_MAXIMUM (127)
    REPORT_SIZE(1),     0x08, //     REPORT_SIZE (8)
    REPORT_COUNT(1),    0x03, //     REPORT_COUNT (3)
    INPUT(1),           0x06, //     INPUT (Data, Variable, Relative) ;3 bytes (X,Y,Wheel)
    // ------------------------------------------------- Horizontal wheel
    USAGE_PAGE(1),      0x0c, //     USAGE PAGE (Consumer Devices)
    USAGE(2),           0x38, 0x02, //     USAGE (AC Pan)
    LOGICAL_MINIMUM(1), 0x81, //     LOGICAL_MINIMUM (-127)
    LOGICAL_MAXIMUM(1), 0x7f, //     LOGICAL_MAXIMUM (127)
    REPORT_SIZE(1),     0x08, //     REPORT_SIZE (8)
    REPORT_COUNT(1),    0x01, //     REPORT_COUNT (1)
    INPUT(1),           0x06, //     INPUT (Data, Var, Rel)
    END_COLLECTION(0),        //   END_COLLECTION
    END_COLLECTION(0),        // END_COLLECTION
    // ========================<[ GAMEPAD 0 ]>========================
    // source : https://github.com/lemmingDev/ESP32-BLE-Gamepad
    // a simple gamepad : 4-direction pad as 4 buttons + 4 buttons (A, B, Start, Select) = 8 buttons
    USAGE_PAGE(1),      0x01, // USAGE_PAGE (Generic Desktop)
    USAGE(1),           0x05, // USAGE (Gamepad)
    COLLECTION(1),      0x01, // COLLECTION (Application)
    REPORT_ID(1),		0x03, //   REPORTID #3
    USAGE_PAGE(1),      0x09, //     USAGE_PAGE (Button)
    USAGE_MINIMUM(1),   0x01, //     USAGE_MINIMUM (Button 1)
    USAGE_MAXIMUM(1),   0x08, //     USAGE_MAXIMUM (Button 8)
    LOGICAL_MINIMUM(1), 0x00, //     LOGICAL_MINIMUM (0)
    LOGICAL_MAXIMUM(1), 0x01, //     LOGICAL_MAXIMUM (1)
    REPORT_SIZE(1),     0x01, //     REPORT_SIZE (1)
    REPORT_COUNT(1),    0x08, //     REPORT_COUNT (5)
    UNIT_EXPONENT(1),   0x00, //     UNIT_EXPONENT (0)
    UNIT(1),            0x00, //     UNIT (None)
    INPUT(1),           0x02, //     INPUT (Data, Variable, Absolute) ;5 button bits
    END_COLLECTION(0),        // END_COLLECTION
    // ========================<[ GAMEPAD 1 ]>========================
    // once again
    USAGE_PAGE(1),      0x01, // USAGE_PAGE (Generic Desktop)
    USAGE(1),           0x05, // USAGE (Gamepad)
    COLLECTION(1),      0x01, // COLLECTION (Application)
    REPORT_ID(1),		0x04, //   REPORTID #4
    USAGE_PAGE(1),      0x09, //     USAGE_PAGE (Button)
    USAGE_MINIMUM(1),   0x01, //     USAGE_MINIMUM (Button 1)
    USAGE_MAXIMUM(1),   0x08, //     USAGE_MAXIMUM (Button 8)
    LOGICAL_MINIMUM(1), 0x00, //     LOGICAL_MINIMUM (0)
    LOGICAL_MAXIMUM(1), 0x01, //     LOGICAL_MAXIMUM (1)
    REPORT_SIZE(1),     0x01, //     REPORT_SIZE (1)
    REPORT_COUNT(1),    0x08, //     REPORT_COUNT (5)
    UNIT_EXPONENT(1),   0x00, //     UNIT_EXPONENT (0)
    UNIT(1),            0x00, //     UNIT (None)
    INPUT(1),           0x02, //     INPUT (Data, Variable, Absolute) ;5 button bits
    END_COLLECTION(0),        // END_COLLECTION
};


/*

*/

ReportMapDescriptor ReportMapProvider::getReportMapForSimpleKeyboard() {
    ReportMapDescriptor* result = new ReportMapDescriptor() ;
    result->data = (uint8_t*)reportMapKeyboard ;
    result->size = sizeof(reportMapKeyboard) ;
}

ReportMapDescriptor ReportMapProvider::getReportMapForCombinedKeyboardMouseGamepadGamepad() {

}