#ifndef FEEDBACK_LED_HPP
#define FEEDBACK_LED_HPP

// standard includes
#include <cstdint>

// esp32 includes

// project includes
#include "AniVal.hpp"

/** @brief The list of feedback sequences.
 */
typedef enum
{
    OFF, ON, //
    BLINK_ONCE, BLINK_TWICE, BLINK_THRICE, //
    FALTER_ONCE, FALTER_TWICE, FALTER_THRICE //
} FeedbackSequence ;


/** @brief Model of a feedback led, a led that blinks following a sequences of on/off states.
 */
class FeedbackLed {
    private:
        AnimatedBool *animations ; // instances of animated sequences
        FeedbackSequence current ; //index of current animation instance
        bool looping ; //if the current animation is looped over.

    public:
        FeedbackLed() ;
        virtual ~FeedbackLed() ;
        void setFeedbackSequenceOnce(FeedbackSequence sequence) ;
        void setFeedbackSequenceAndLoop(FeedbackSequence sequence) ;
        // get the next value of the led
        bool next() ;

} ;

#endif