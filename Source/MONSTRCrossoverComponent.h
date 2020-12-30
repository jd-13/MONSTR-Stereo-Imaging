/*
 *	File:		MONSTRCrossoverComponent.h
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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MONSTRLookAndFeel.h"
#include "PluginProcessor.h"
#include "ParameterData.h"
#include "General/CoreMath.h"
#include <memory>
#include <array>

class MONSTRCrossoverComponent : public Component {
public:

    MONSTRCrossoverComponent(MonstrAudioProcessor* newAudioProcessor);
    virtual ~MONSTRCrossoverComponent();

    void updateParameters();

    void paint(Graphics& g) override;

    void mouseDrag(const MouseEvent& event) override;

private:

    constexpr static int SLIDER_THUMB_RADIUS {6};

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


    std::array<double, WECore::MONSTR::Parameters::_MAX_NUM_BANDS - 1> _crossoverValues;
    std::array<double, WECore::MONSTR::Parameters::_MAX_NUM_BANDS> _bandWidths;
    std::array<bool, WECore::MONSTR::Parameters::_MAX_NUM_BANDS> _bandActives;

    MonstrAudioProcessor* _processor;

    void _drawNeutralLine(Graphics& g);

    void _drawSine(Graphics& g,
                   float crossoverLowerHz,
                   float crossoverUpperHz);

    void _drawSliderThumbs(Graphics& g,
                           float crossoverLowerXPos,
                           float crossoverUpperXPos);

    void _drawWidthRectangles(Graphics& g,
                              int crossoverLowerXPos,
                              int crossoverUpperXPos);

    void _drawFrequencyText(Graphics& g,
                            int crossoverLowerXPos,
                            float crossoverLowerHz,
                            int crossoverUpperXPos,
                            float crossoverUpperHz);
};
