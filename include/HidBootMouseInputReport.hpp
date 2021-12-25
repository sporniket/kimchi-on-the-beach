#ifndef HID_BOOT_MOUSE_INPUT_REPORT_HPP
#define HID_BOOT_MOUSE_INPUT_REPORT_HPP

// standard includes
#include <cstdint>

// esp32 includes

// project includes
class HidBootMouseInputReport ;
typedef enum {
    REPORT_CHANGED_FOR_MOUSE
} HidBootMouseInputReportEventType ;
typedef struct {
    HidBootMouseInputReportEventType type ;
    HidBootMouseInputReport* source ;
} HidBootMouseInputReportEvent ;

class HidBootMouseInputReportListener {
    public:
        virtual ~HidBootMouseInputReportListener() ;
        virtual void onHidBootMouseInputReportEvent(HidBootMouseInputReportEvent* event) = 0 ;
} ;

/** @brief Manage the input report of a mouse that is sent through hid protocol, compatible with boot protocole.
 * 
 * Use the press/release/move functions following a fluent syntax, then call notify. e.g. 
 * <code>report.pressLeft()->releaseRight()->moveXy(x,y)->notify()</code>
 */
class HidBootMouseInputReport {
    private:
        const uint8_t SIZE_OF_REPORT = 5 ;
        /**
         * @brief the report.
         * 
         * 1st byte : 5 bits for 5 mouse buttons
         * 3 bytes : X, Y, Wheel, signed byte
         * 1 byte : AC pan, signed byte
         * 
         * see also https://www.microchip.com/forums/m391435.aspx
         * 
         * Note : boot mouse protocole requires only 3 bytes, the mouse buttons (3 buttons), x and y.
         */
        uint8_t report[5] = {0x0, 0x0, 0x0, 0x0,0x0} ; 

        /**
         * @brief The listener. (TODO : support multiple listeners)
         */
        HidBootMouseInputReportListener *listener ;
        inline void resetReport() {
            for(uint8_t i = 0 ; i < SIZE_OF_REPORT ; i++) {
                report[i] = 0 ;
            }
        }

    public:
        const uint8_t BUTTON_LEFT__PRESS = 0b1;
        const uint8_t BUTTON_RIGHT__PRESS = 0b10;
        const uint8_t BUTTON_MIDDLE__PRESS = 0b100;
        const uint8_t BUTTON_BACK__PRESS = 0b1000;
        const uint8_t BUTTON_FORWARD__PRESS = 0b10000;
        const uint8_t BUTTON_LEFT__RELEASE = 0b11110;
        const uint8_t BUTTON_RIGHT__RELEASE = 0b11101;
        const uint8_t BUTTON_MIDDLE__RELEASE = 0b11011;
        const uint8_t BUTTON_BACK__RELEASE = 0b10111;
        const uint8_t BUTTON_FORWARD__RELEASE = 0b01111;
        
        virtual ~HidBootMouseInputReport() ;

        inline HidBootMouseInputReport* withListener(HidBootMouseInputReportListener* listenerImpl) {
            listener = listenerImpl ;
            return this ;
        }

        inline void notify() {
            if (nullptr != listener) {
                HidBootMouseInputReportEvent event = {.type = REPORT_CHANGED_FOR_MOUSE, .source = this } ;
                listener->onHidBootMouseInputReportEvent(&event);
            }
            //resetReport();
        }

        /**
         * @brief Shorthand to release all the buttons.
         * 
         * @return HidBootMouseInputReport* 
         */
        inline HidBootMouseInputReport* clearButton() {report[0] = 0 ; return this ;}
        inline HidBootMouseInputReport* pressLeft() {report[0] |= BUTTON_LEFT__PRESS ; return this ;}
        inline HidBootMouseInputReport* pressRight() {report[0] |= BUTTON_RIGHT__PRESS ; return this ;}
        inline HidBootMouseInputReport* pressMiddle() {report[0] |= BUTTON_MIDDLE__PRESS ; return this ;}
        inline HidBootMouseInputReport* pressBack() {report[0] |= BUTTON_BACK__PRESS ; return this ;}
        inline HidBootMouseInputReport* pressForward() {report[0] |= BUTTON_FORWARD__PRESS ; return this ;}

        inline HidBootMouseInputReport* releaseLeft() {report[0] &= BUTTON_LEFT__RELEASE ; return this ;}
        inline HidBootMouseInputReport* releaseRight() {report[0] &= BUTTON_RIGHT__RELEASE ; return this ;}
        inline HidBootMouseInputReport* releaseMiddle() {report[0] &= BUTTON_MIDDLE__RELEASE ; return this ;}
        inline HidBootMouseInputReport* releaseBack() {report[0] &= BUTTON_BACK__RELEASE ; return this ;}
        inline HidBootMouseInputReport* releaseForward() {report[0] &= BUTTON_FORWARD__RELEASE ; return this ;}

        inline HidBootMouseInputReport* move(int8_t x, int8_t y, int8_t w, int8_t p) {
            report[1] = uint8_t(x) ; 
            report[2] = uint8_t(y) ; 
            report[3] = uint8_t(w) ; 
            report[4] = uint8_t(p) ; 
            return this ;
        }
        inline HidBootMouseInputReport* moveCursor(int8_t x, int8_t y) {return move(x, y, 0, 0) ;}
        inline HidBootMouseInputReport* moveWheel(int8_t w) {return move(0,0,w,0) ;}
        inline HidBootMouseInputReport* moveAcPan(int8_t p) {return move(0,0,0,p) ;}

        inline uint8_t* getReport() {return report ;}
        inline uint8_t getSizeOfReport() {return SIZE_OF_REPORT;}

} ;

#endif