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
    parameter(newParameter) {
}

void MONSTRWidthSlider::mouseDown(const juce::MouseEvent &event) {
    if (event.mods.isRightButtonDown()) {
        setEnabled(!isEnabled());
        ourProcessor->setParameter(parameter, isEnabled());
    }
    
    Slider::mouseDown(event);
}