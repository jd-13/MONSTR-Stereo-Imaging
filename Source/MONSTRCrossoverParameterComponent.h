/*
 *	File:		MONSTRCrossoverParameterComponent.h
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

#include <array>
#include <memory>
#include <optional>

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class MONSTRWidthLabel;


/**
 * Draws the clickable parts of the crossover component.
 */
class MONSTRCrossoverParameterComponent : public Component {
public:

    MONSTRCrossoverParameterComponent(MonstrAudioProcessor* newAudioProcessor);
    virtual ~MONSTRCrossoverParameterComponent() = default;

    void paint(Graphics& g) override;

private:
    MonstrAudioProcessor* _processor;

    void _drawNeutralLine(Graphics& g);

    void _drawSliderThumbs(Graphics& g);

    void _drawWidthRectangles(Graphics& g);

    void _drawFrequencyText(Graphics& g);

    void _drawBandButtons(Graphics& g);
};
