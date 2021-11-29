#ifndef HID_KEYBOARD_STATE_HPP
#define HID_KEYBOARD_STATE_HPP

// standard includes
#include <cstdint>

// esp32 includes

// project includes

// event handling.
class HidBootKeyboardInputReport ;
typedef enum {
    REPORT_CHANGED
} HidBootKeyboardInputReportEventType ;
typedef struct {
    HidBootKeyboardInputReportEventType type ;
    HidBootKeyboardInputReport* source ;
} HidBootKeyboardInputReportEvent ;

class HidBootKeyboardInputReportListener {
    public:
        virtual ~HidBootKeyboardInputReportListener() ;
        virtual void onHidBootKeyboardInputReportEvent(HidBootKeyboardInputReportEvent* event) = 0 ;
} ;

/** @brief Manage the input report for a keyboard that is sent through HID protocole.
 */
class HidBootKeyboardInputReport {
    private:
        const uint8_t FIRST_KEY_SLOT = 2 ;
        const uint8_t MAX_KEY_SLOT = 8 ;
        const uint8_t NO_KEY_SLOT_FOUND = 8 ;
        const uint8_t SIZE_OF_REPORT = 8 ;
        /**
         * @brief The actual HID keyboard report, following the "Boot Interface Descriptors".
         * 
         * @see https://www.usb.org/sites/default/files/hid1_11.pdf pp. 59~60.
         * 
         * The first byte is a bitmap, where each bit is the status of a modifier key (control, alt, shift, meta ; left or right).
         * 
         * The second byte is reserved for OEM, it will be kept to 0.
         * 
         * Then up to 6 non-modifier keys are kept up to date.
         */
        uint8_t report[8] = {0x0, 0x0, 0x0, 0x0,0x0,0x0,0x0,0x0} ; 

        /**
         * @brief The listener. (TODO : support multiple listeners)
         */
        HidBootKeyboardInputReportListener* listener ;

        /**
         * @brief Find a free slot for a new key press.
         * 
         * @return uint8_t either a valid slot index, either NO_KEY_SLOT_FOUND.
         */
        inline uint8_t findFreeSlot() {
            return findSlotWithKey(0) ;
        }

        /**
         * @brief Find the slot having the given hid value.
         * 
         * @param key the hid value to find.
         * @return uint8_t either a valid slot index, either NO_KEY_SLOT_FOUND.
         */
        inline uint8_t findSlotWithKey(uint8_t key) {
            for(uint8_t slot = FIRST_KEY_SLOT ; slot < MAX_KEY_SLOT ; slot++) {
                if (key == report[slot]) return slot ;
            }
            return NO_KEY_SLOT_FOUND ;
        }

    public:
        virtual ~HidBootKeyboardInputReport() ;

        inline HidBootKeyboardInputReport* withListener(HidBootKeyboardInputReportListener* listenerImpl) {
            listener = listenerImpl ;
            return this ;
        }

        inline void notify() {
            if (nullptr != listener) {
                HidBootKeyboardInputReportEvent event = {.type = REPORT_CHANGED, .source = this } ;
                listener->onHidBootKeyboardInputReportEvent(&event);
            }
        }

        /**
         * @brief Update the report and notify listeners for the change, for a regular key press.
         * 
         * When there are no more free slot, the key press is ignored.
         * 
         * @param key the HID key value.
         */
        inline void registerKeyPress(uint8_t key) {
            uint8_t slot = findFreeSlot() ;
            if (NO_KEY_SLOT_FOUND != slot) {
                report[slot] = key ;
                notify() ;
            }
        }

        /**
         * @brief Update the report and notify listeners for the change, for a regular key press.
         * 
         * When there are no more free slot, the key press is ignored.
         * 
         * @param key the HID key value.
         */
        inline void registerKeyRelease(uint8_t key) {
            uint8_t slot = findSlotWithKey(key) ;
            if (NO_KEY_SLOT_FOUND != slot) {
                report[slot] = 0 ;
                notify() ;
            }
        }

        inline void registerModifierPress(uint8_t modifier) {
            report[0] = (report[0] & (~modifier)) + modifier ;
            notify() ;
        }

        inline void registerModifierRelease(uint8_t modifier) {
            report[0] = report[0] & (~modifier) ;
            notify() ;
        }

        inline uint8_t* getReport() {return report ;}
        inline uint8_t getSizeOfReport() {return SIZE_OF_REPORT;}

} ;

#endif