/*
 *    File:        MONSTRLookAndFeel.h
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

#ifndef MONSTRLOOKANDFEEL_H_INCLUDED
#define MONSTRLOOKANDFEEL_H_INCLUDED

#define _USE_MATH_DEFINES

#include "../JuceLibraryCode/JuceHeader.h"
#include "MONSTRCrossoverComponent.h"
#include "math.h"

class MONSTRLookAndFeel : public LookAndFeel_V2 {
public:
    MONSTRLookAndFeel();
    
    ~MONSTRLookAndFeel();
    
    virtual void drawLinearSliderThumb(Graphics& g,
                                       int x,
                                       int y,
                                       int width,
                                       int height,
                                       float sliderPos,
                                       float minSliderPos,
                                       float maxSliderPos,
                                       const Slider::SliderStyle style,
                                       Slider& slider) override;
    
    virtual void drawLinearSliderBackground(Graphics& g,
                                            int x,
                                            int y,
                                            int width,
                                            int height,
                                            float sliderPos,
                                            float minSliderPos,
                                            float maxSliderPos,
                                            const Slider::SliderStyle style,
                                            Slider& slider) override;
    
    virtual void drawTooltip(Graphics& g,
                             const String& text,
                             int width,
                             int height) override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MONSTRLookAndFeel)
    
    static const Colour lightGrey,
                        darkGrey;
};



#endif  // MONSTRLOOKANDFEEL_H_INCLUDED
