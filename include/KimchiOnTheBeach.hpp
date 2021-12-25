#ifndef KIMCHI_ON_THE_BEACH_HPP
#define KIMCHI_ON_THE_BEACH_HPP

// standard includes
#include <cstdint>

// esp32 includes
#include <esp_log.h>

// project includes

// -- BEGIN from snippets
#include "BLEHIDDevice.h"
// -- END from snippets

#include "InputButton.hpp"
#include "HidBootKeyboardInputReport.hpp"
#include "HidBootMouseInputReport.hpp"

enum KimchiReportIdOfInput {
    KEYBOARD = 1,
    MOUSE,
    GAMEPAD_0,
    GAMEPAD_1
}  ;

enum KimchiInputChannel {
    CHANNEL_KEYBOARD,CHANNEL_MOUSE,CHANNEL_GAMEPAD_0,CHANNEL_GAMEPAD_1
    ,COUNT //the number of channel inputs to size an array.
} ; 

#define KIMCHI_INPUT_CHANNEL_COUNT 4

/** @brief What the class is for.
 */
class KimchiOnTheBeach : public InputButtonListener, public HidBootKeyboardInputReportListener, public HidBootMouseInputReportListener {
    private:
        HidBootKeyboardInputReport reportOfKeyboard ;
        HidBootMouseInputReport reportOfMouse ;
        
        bool started = false;
        BLECharacteristic * inputChannel[KimchiInputChannel::COUNT] ;

    public:
        KimchiOnTheBeach() ;
        virtual ~KimchiOnTheBeach() ;
        inline KimchiOnTheBeach* withBleHidDevice(BLEHIDDevice* device) {
            inputChannel[int(KimchiInputChannel::CHANNEL_KEYBOARD)] = device->inputReport(uint8_t(KimchiReportIdOfInput::KEYBOARD));
            inputChannel[int(KimchiInputChannel::CHANNEL_MOUSE)] = device->inputReport(uint8_t(KimchiReportIdOfInput::MOUSE));
            //inputChannel[KimchiInputChannel::CHANNEL_GAMEPAD_0] = device->inputReport(KimchiReportIdOfInput::GAMEPAD_0);
            //inputChannel[KimchiInputChannel::CHANNEL_GAMEPAD_1] = device->inputReport(KimchiReportIdOfInput::GAMEPAD_1);
            return this;
        }
        inline bool isStarted() {return started ;}
        inline void start() {started = true ;}
        inline void stop() {started = false ;}

        //event handlers
        void onInputButtonEvent(InputButtonEvent* event) ;
        void onHidBootKeyboardInputReportEvent(HidBootKeyboardInputReportEvent* event) ;
        void onHidBootMouseInputReportEvent(HidBootMouseInputReportEvent* event) ;
} ;

#endif