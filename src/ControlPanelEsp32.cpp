
// header include
#include "ControlPanelEsp32.hpp"

//====================================================================
// GPIO pins affectation from configuration
#define PIN_STATUS_MAIN gpio_num_t(CONFIG_PIN_STATUS_MAIN)
#define PIN_STATUS_ALT gpio_num_t(CONFIG_PIN_STATUS_ALT)
#define PIN_STATUS_RGB_RED gpio_num_t(CONFIG_PIN_STATUS_RGB_RED)
#define PIN_STATUS_RGB_GREEN gpio_num_t(CONFIG_PIN_STATUS_RGB_GREEN)
#define PIN_STATUS_RGB_BLUE gpio_num_t(CONFIG_PIN_STATUS_RGB_BLUE)

ControlPanelEsp32::~ControlPanelEsp32(){}
// write code here...

ControlPanelEsp32::ControlPanelEsp32(GeneralPurposeInputOutput* gpioImpl) 
    : gpio(gpioImpl) 
{

}

class LedUpdaterTask : public Task {
    public:
        ControlPanelEsp32* controlPanel ;
        void run(void *data) {
            const TickType_t SLEEP_TIME = 100 / portTICK_PERIOD_MS ; // 10 Hz
            GeneralPurposeInputOutput* gpio = controlPanel->getGpio();
            while(true) {
                gpio->getDigital()->write(CONFIG_PIN_STATUS_MAIN, controlPanel->getMainLed()->next());
                vTaskDelay(SLEEP_TIME);
            }
            
        }
} ;

class ButtonWatcherTask : public Task {
    public:
        ControlPanelEsp32* controlPanel ;
        void run(void *data) {
            const TickType_t SLEEP_TIME = 20 / portTICK_PERIOD_MS ; // 50 Hz
            GeneralPurposeInputOutput* gpio = controlPanel->getGpio();
            while(true) {
                controlPanel->getActionWhite()->update(gpio->getDigital()->read(CONFIG_PIN_BUTTON_ACTION_WHITE));
                controlPanel->getLeftYellow()->update(gpio->getDigital()->read(CONFIG_PIN_BUTTON_LEFT_YELLOW));
                controlPanel->getDownGreen()->update(gpio->getDigital()->read(CONFIG_PIN_BUTTON_DOWN_GREEN));
                controlPanel->getUpBlue()->update(gpio->getDigital()->read(CONFIG_PIN_BUTTON_UP_BLUE));
                controlPanel->getRightRed()->update(gpio->getDigital()->read(CONFIG_PIN_BUTTON_RIGHT_RED));
                vTaskDelay(SLEEP_TIME);
            }
        }
} ;

void ControlPanelEsp32::start() {
    // setup gpios
    gpio->getDigital()->setup(CONFIG_PIN_STATUS_MAIN, WRITE) ;
    gpio->getDigital()->setup(CONFIG_PIN_BUTTON_ACTION_WHITE, READ);
    gpio->getDigital()->setup(CONFIG_PIN_BUTTON_LEFT_YELLOW, READ);
    gpio->getDigital()->setup(CONFIG_PIN_BUTTON_DOWN_GREEN, READ);
    gpio->getDigital()->setup(CONFIG_PIN_BUTTON_UP_BLUE, READ);
    gpio->getDigital()->setup(CONFIG_PIN_BUTTON_RIGHT_RED, READ);
    actionWhite.withDebouncer(DEBOUNCER_TYPICAL) ;
    leftYellow.withDebouncer(DEBOUNCER_TYPICAL) ;
    downGreen.withDebouncer(DEBOUNCER_TYPICAL) ;
    upBlue.withDebouncer(DEBOUNCER_TYPICAL) ;
    rightRed.withDebouncer(DEBOUNCER_TYPICAL) ;

    // setup and start led task
    LedUpdaterTask *updateTask = new LedUpdaterTask() ;
    updateTask->controlPanel = this ;
    updateTask->start();
    ledsUpdater = updateTask ;

    // setup and start button watcher tasks
    ButtonWatcherTask *watcherTask = new ButtonWatcherTask() ;
    watcherTask->controlPanel = this ;
    watcherTask->start();
    buttonWatcher = watcherTask ;
}