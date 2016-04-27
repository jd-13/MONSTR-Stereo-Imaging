/*
  ==============================================================================

    MONSTRLookAndFeel.cpp
    Created: 1 Mar 2016 6:51:29pm
    Author:  Jack Devlin

  ==============================================================================
*/

#include "MONSTRLookAndFeel.h"

// Initialise static members
const Colour MONSTRLookAndFeel::lightGrey(200, 200, 200);
const Colour MONSTRLookAndFeel::darkGrey(107, 107, 107);


MONSTRLookAndFeel::MONSTRLookAndFeel() : LookAndFeel_V2() {
}

MONSTRLookAndFeel::~MONSTRLookAndFeel() {
    
}


void MONSTRLookAndFeel::drawLinearSliderThumb(Graphics& /*g*/,
                                              int /*x*/,
                                              int /*y*/,
                                              int /*width*/,
                                              int /*height*/,
                                              float /*sliderPos*/,
                                              float /*minSliderPos*/,
                                              float /*maxSliderPos*/,
                                              const Slider::SliderStyle /*style*/,
                                              juce::Slider& /*slider*/) {
    // do nothing
}

void MONSTRLookAndFeel::drawLinearSliderBackground(Graphics& /*g*/,
                                                   int /*x*/,
                                                   int /*y*/,
                                                   int /*width*/,
                                                   int /*height*/,
                                                   float /*sliderPos*/,
                                                   float /*minSliderPos*/,
                                                   float /*maxSliderPos*/,
                                                   const Slider::SliderStyle /*style*/,
                                                   Slider& /*slider*/) {
    // do nothing
}

void MONSTRLookAndFeel::drawTooltip(Graphics& g,
                                     const String& text,
                                     int width,
                                     int height) {
    g.setColour(lightGrey);
    g.fillRect(0, 0, width, height);
    
    g.setColour(darkGrey);
    g.drawFittedText(text, 0, 0, width, height, Justification::centred, 3);
}