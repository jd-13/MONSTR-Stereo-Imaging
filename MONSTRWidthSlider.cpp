/*
  ==============================================================================

    MONSTRWidthSlider.cpp
    Created: 9 Apr 2016 5:08:55pm
    Author:  Jack Devlin

  ==============================================================================
*/

#include "MONSTRWidthSlider.h"
MONSTRWidthSlider::MONSTRWidthSlider(String name,
                                     MonstrAudioProcessor* newProcessor,
                                     int newParameter)
:  Slider(name),                                                                            ourProcessor(newProcessor),
    isBandActive(true),
    parameter(newParameter) {
}

void MONSTRWidthSlider::mouseDown(const juce::MouseEvent &event) {
    if (event.mods.isRightButtonDown()) {
        isBandActive = !isBandActive;
        ourProcessor->setParameter(parameter, isBandActive);
    }
    
    Slider::mouseDown(event);
}

bool MONSTRWidthSlider::getIsBandActive() {
    return isBandActive;
}

void MONSTRWidthSlider::setIsBandActive(bool val) {
    isBandActive = val;
}