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