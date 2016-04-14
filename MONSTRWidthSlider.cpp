/*
  ==============================================================================

    MONSTRWidthSlider.cpp
    Created: 9 Apr 2016 5:08:55pm
    Author:  Jack Devlin

  ==============================================================================
*/

#include "MONSTRWidthSlider.h"
MONSTRWidthSlider::MONSTRWidthSlider(String name) : Slider(name), isBandActive(true) {
}

void MONSTRWidthSlider::mouseDown(const juce::MouseEvent &event) {
    if (event.mods.isRightButtonDown()) {
        isBandActive = !isBandActive;
    }
    
    Slider::mouseDown(event);
}

bool MONSTRWidthSlider::getIsBandActive() {
    return isBandActive;
}