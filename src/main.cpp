#include "driver/gpio.h"
#include "driver/timer.h"

// sdk config
#include "sdkconfig.h"

// project includes
#include "GeneralPurposeInputOutput.hpp"
#include "DigitalInputOutputEsp32.hpp"
#include "ControlPanelEsp32.hpp"


//====================================================================
// GPIO pins affectation from configuration
#define PIN_BUTTON_ACTION_WHITE gpio_num_t(CONFIG_PIN_BUTTON_ACTION_WHITE)
#define PIN_BUTTON_LEFT_YELLOW gpio_num_t(CONFIG_PIN_BUTTON_LEFT_YELLOW)
#define PIN_BUTTON_DOWN_GREEN gpio_num_t(CONFIG_PIN_BUTTON_DOWN_GREEN)
#define PIN_BUTTON_UP_BLUE gpio_num_t(CONFIG_PIN_BUTTON_UP_BLUE)
#define PIN_BUTTON_RIGHT_RED gpio_num_t(CONFIG_PIN_BUTTON_RIGHT_RED)

//====================================================================
// from timer group sample code
#define TIMER_DIVIDER (16)                                     //  Hardware timer clock divider
#define TIMER_SCALE (TIMER_BASE_CLK / TIMER_DIVIDER)           // convert counter value to seconds
#define TIMER_SCALE_MS (TIMER_BASE_CLK / TIMER_DIVIDER / 1000) // convert counter value to milliseconds

/**
 * Main file for running the BLE samples.
 */
extern "C" {
	void app_main(void);
}

void SampleHID(ControlPanelEsp32* controlPanel) ;

GeneralPurposeInputOutput* gpio ;
ControlPanelEsp32* controlPanel ;




void app_main(void) {
	// setup
	gpio = (new GeneralPurposeInputOutput())
		->withDigital(new DigitalInputOutputEsp32()) ;
	controlPanel = (new ControlPanelEsp32(gpio)) ;
	controlPanel->getMainLed()->setFeedbackSequenceAndLoop(BLINK_ONCE) ;
	controlPanel->start() ;
	/* Configure the IOMUX register for pad BLINK_GPIO (some pads are
	muxed to GPIO on reset already, but some default to other
	functions and need to be switched to GPIO. Consult the
	Technical Reference for a list of pads and their default
	functions.)
	*/

	// launch tasks
	SampleHID(controlPanel);
} // app_main
