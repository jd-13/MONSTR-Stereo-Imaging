/*
 *	File:		MONSTRCrossover.h
 *
 *	Version:	1.0.0
 *
 *	Created:	06/03/2016
 *
 *	This file is part of MONSTR.
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

#ifndef MONSTRCROSSOVERBACKGROUND_H_INCLUDED
#define MONSTRCROSSOVERBACKGROUND_H_INCLUDED

#define _USE_MATH_DEFINES

#include "../JuceLibraryCode/JuceHeader.h"
#include "MONSTRLookAndFeel.h"
#include "MONSTRWidthSlider.h"
#include "ParameterData.h"
#include "math.h"
#include <memory>
#include <array>

class MONSTRCrossover {
public:
    
    MONSTRCrossover() = delete;
    
    /* update
     *
     * Updates the graphics being drawn behind the crossover.
     *
     * args: g              Graphics object to use to draw the crossover
     *       bounds         Int rectangle defining the area to draw within
     *       lowerSlider    The (horizontal) slider to determine the lower
     *                      frequency of the crossover
     *       upperSlider    The (horizontal) slider to determine the upper
     *                      frequency of the crossover
     *       width1Sld      The (vertical) slider to determine the stereo width
     *                      of the lower band
     *       width2Sld      The (vertical) slider to determine the stereo width
     *                      of the middle band
     *       width3Sld      The (vertical) slider to determine the stereo width
     *                      of the upper band
     */
    static void update(Graphics& g,
                       const Rectangle<int>& bounds,
                       Slider& lowerSlider,
                       Slider& upperSlider,
                       MONSTRWidthSlider& width1Sld,
                       MONSTRWidthSlider& width2Sld,
                       MONSTRWidthSlider& width3Sld);
    
private:
    static void resizeWidthSliders(Graphics& g,
                                   const Rectangle<int>& bounds,
                                   int crossoverLowerXPos,
                                   int crossoverUpperXPos,
                                   MONSTRWidthSlider& width1Sld,
                                   MONSTRWidthSlider& width2Sld,
                                   MONSTRWidthSlider& width3Sld);
    
    static void drawSine(Graphics& g,
                         Rectangle<int> bounds,
                         float crossoverLowerHz,
                         float crossoverUpperHz);
    
    static void drawWidthRectangles(Graphics& g,
                                    const Rectangle<int>& bounds,
                                    int crossoverLowerXPos,
                                    int crossoverUpperXPos,
                                    MONSTRWidthSlider& width1Sld,
                                    MONSTRWidthSlider& width2Sld,
                                    MONSTRWidthSlider& width3Sld);
    
    static void drawNeutralLine(Graphics& g,
                                Rectangle<int> bounds);
    
    static void positionHorizontalSliders(const Rectangle<int>& bounds,
                                          Slider& crossoverLowerSld,
                                          Slider& crossoverUpperSld);
    static void drawFrequencyText(Graphics& g,
                                  const Rectangle<int>& bounds,
                                  int crossoverLowerXPos,
                                  float crossoverLowerHz,
                                  int crossoverUpperXPos,
                                  float crossoverUpperHz);
    
    static void drawSliderThumbs(Graphics& g,
                                 const Rectangle<int>& bounds,
                                 float crossoverLowerXPos,
                                 float crossoverUpperXPos);
    
    
    static bool needsSetup;
    
    // defines the fraction of the distance from the top and bottom
    // of the crossover GUI element which represents neutral stereo width
    constexpr static const float neutralPos {0.25};
    
    // decrease the scaling coefficient to increase the on-screen space
    // used by the lower frequencies
    constexpr static const int scaleCoefficient {20};
    
    constexpr static const int sliderThumbRadius {6};
    
    static std::array<double, 200>sineWaveTable;
    
    static const Colour lightGrey,
                        darkGrey,
                        red,
                        yellow,
                        green,
                        redTrans,
                        yellowTrans,
                        greenTrans,
                        lightGreyTrans;
};

#endif  // MONSTRCROSSOVERBACKGROUND_H_INCLUDED
