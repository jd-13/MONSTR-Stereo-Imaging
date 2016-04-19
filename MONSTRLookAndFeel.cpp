/*
  ==============================================================================

    MONSTRLookAndFeel.cpp
    Created: 1 Mar 2016 6:51:29pm
    Author:  Jack Devlin

  ==============================================================================
*/

#include "MONSTRLookAndFeel.h"

// Initialise static members



MONSTRLookAndFeel::MONSTRLookAndFeel() : LookAndFeel_V2() {
}

MONSTRLookAndFeel::~MONSTRLookAndFeel() {
    
}


void MONSTRLookAndFeel::drawLinearSliderThumb(Graphics &g,
                                              int /*x*/,
                                              int y,
                                              int /*width*/,
                                              int height,
                                              float sliderPos,
                                              float /*minSliderPos*/,
                                              float /*maxSliderPos*/,
                                              const Slider::SliderStyle style,
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