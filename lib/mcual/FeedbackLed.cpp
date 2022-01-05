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


// header include
#include "FeedbackLed.hpp"

FeedbackLed::~FeedbackLed(){}
// write code here...

FeedbackLed::FeedbackLed() {
    animations = (new AnimatedBool(AnimatedBool::createAnimation('*', ".")))     // off
        ->append(AnimatedBool::createAnimation('*', "*")) // on
        ->append(AnimatedBool::createAnimation('*', ".*........")) // blink once
        ->append(AnimatedBool::createAnimation('*', ".*.*......")) // blink twice
        ->append(AnimatedBool::createAnimation('*', ".*.*.*....")) // blink thrice
        ->append(AnimatedBool::createAnimation('.', ".*........")) // falter once
        ->append(AnimatedBool::createAnimation('.', ".*.*......")) // falter twice
        ->append(AnimatedBool::createAnimation('.', ".*.*.*....")) // falter thrice
    ;
}

void FeedbackLed::setFeedbackSequenceOnce(FeedbackSequence sequence) {
    animations->setCurrentAnimation(sequence) ;
    looping = false ; 
}

void FeedbackLed::setFeedbackSequenceAndLoop(FeedbackSequence sequence) {
    animations->setCurrentAnimation(sequence) ;
    looping = true ; 
}

bool FeedbackLed::next() {
    return looping ? animations->run() : animations->runOnce() ;
}