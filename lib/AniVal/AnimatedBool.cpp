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


#include "AniVal.hpp"

std::vector<bool> *AnimatedBool::createAnimation(char asTrue, const std::string sequence)
{
    std::vector<bool> *result = new std::vector<bool>();
    result->reserve(sequence.size());
    for (const char &c : sequence)
    {
        bool item = (c == asTrue);
        result->push_back(item);
    }
    return result;
}

void AnimatedBool::handleCurrentChanged() { animationIterator = animationList[current]->begin(); }

AnimatedBool::AnimatedBool(std::vector<bool> *animation)
{
    append(animation);
    handleCurrentChanged();
};

AnimatedBool *AnimatedBool::append(std::vector<bool> *animation)
{
    animationList.push_back(animation);
    return this;
}

int AnimatedBool::getAnimationCount() { return animationList.size(); }

int AnimatedBool::setCurrentAnimation(int value)
{
    if (value < 0 || value >= getAnimationCount())
    {
        return current;
    }
    current = value;
    handleCurrentChanged();
    return current;
}

bool AnimatedBool::run()
{
    if (0 == animationList[current]->size())
    {
        return false;
    }
    ++animationIterator;
    if (animationIterator == animationList[current]->end())
    {
        animationIterator = animationList[current]->begin();
    }
    return value();
}

bool AnimatedBool::runOnce()
{
    if (0 == animationList[current]->size())
    {
        return false;
    }
    if (animationIterator != animationList[current]->end())
    {
        ++animationIterator;
    }
    return value();
}

bool AnimatedBool::value() { return *animationIterator; }
