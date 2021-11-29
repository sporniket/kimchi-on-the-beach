
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