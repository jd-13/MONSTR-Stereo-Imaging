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

class MONSTRCrossover : public Component {
public:
    
    MONSTRCrossover(String name,
                    Slider* newCrossoverLowerSld,
                    Slider* newCrossoverUpperSld,
                    MONSTRWidthSlider* newWidth1Sld,
                    MONSTRWidthSlider* newWidth2Sld,
                    MONSTRWidthSlider* newWidth3Sld);
    
    void paint(Graphics& g) override;
    
    void positionHorizontalSliders();
        
private:
    void resizeWidthSliders(int crossoverLowerXPos,
                            int crossoverUpperXPos);
    
    void drawSine(Graphics& g,
                  float crossoverLowerHz,
                  float crossoverUpperHz);
    
    void drawWidthRectangles(Graphics& g,
                             int crossoverLowerXPos,
                             int crossoverUpperXPos);
    
    void drawNeutralLine(Graphics& g);
    
    void drawFrequencyText(Graphics& g,
                           int crossoverLowerXPos,
                           float crossoverLowerHz,
                           int crossoverUpperXPos,
                           float crossoverUpperHz);
    
    void drawSliderThumbs(Graphics& g,
                          float crossoverLowerXPos,
                          float crossoverUpperXPos);
    
        
    // defines the fraction of the distance from the top and bottom
    // of the crossover GUI element which represents neutral stereo width
    constexpr static const float neutralPos {0.25};
    
    // decrease the scaling coefficient to increase the on-screen space
    // used by the lower frequencies
    constexpr static const int scaleCoefficient {20};
    
    constexpr static const int sliderThumbRadius {6};
    
    std::array<double, 200>sineWaveTable;
    
    static const Colour lightGrey,
                        darkGrey,
                        red,
                        yellow,
                        green,
                        redTrans,
                        yellowTrans,
                        greenTrans,
                        lightGreyTrans;
    
    Slider  *crossoverLowerSld,
            *crossoverUpperSld,
            *width1Sld,
            *width2Sld,
            *width3Sld;
};

#endif  // MONSTRCROSSOVERBACKGROUND_H_INCLUDED
