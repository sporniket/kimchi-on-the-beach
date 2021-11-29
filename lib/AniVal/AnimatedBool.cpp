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
