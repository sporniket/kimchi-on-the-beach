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

// interfaces
// Animated values library
// An animated value is a collection of values that can be iterated upon.

#include <string>
#include <vector>

class AnimatedBool
{
  private:
    std::vector<std::vector<bool> *> animationList;
    int current = 0;
    bool ready = false;
    std::vector<bool>::iterator animationIterator;
    void handleCurrentChanged();

  public:
    /**
     * Helper to create an animation from a codified string.
     *
     * @param asTrue char for coding a true, any other char will be coding a false
     * @param sequence string to parse.
     * @returns an animated bool.
     */
    static std::vector<bool> *createAnimation(char asTrue, std::string sequence);

    /**
     * Create an animated boolean with a first animation.
     */
    AnimatedBool(std::vector<bool> *animation);

    /**
     * Add another animation in the animation list.
     */
    AnimatedBool *append(std::vector<bool> *animation);

    /**
     * Get the animation set size, one cannot set the current animation outside this range.
     */
    int getAnimationCount();

    /**
     * Change the animation, nothing happens if the value is out of range.
     *
     * @param value the index of the animation in the list.
     * @returns the actual animation index.
     */
    int setCurrentAnimation(int value);

    /**
     * Advance/loop the current animation.
     *
     * @returns the current value.
     */
    bool run();
    /**
     * Advance the current animation until the end, without looping ; when at the end, return the last value.
     *
     * @returns the current value.
     */
    bool runOnce();
    /**
     * Get the current value.
     *
     * @returns the current value.
     */
    bool value();
};
