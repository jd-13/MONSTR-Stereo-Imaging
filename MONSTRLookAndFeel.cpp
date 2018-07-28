/*
 *    File:        MONSTRLookAndFeel.cpp
 *
 *    Version:    1.0.0
 *
 *    Created:    01/03/2016
 *
 *    This file is part of MONSTR.
 *
 *  MONSTR is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MONSTR is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with MONSTR.  If not, see <http://www.gnu.org/licenses/>.
 *
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
