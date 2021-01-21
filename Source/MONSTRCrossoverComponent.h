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

#include <array>
#include <memory>
#include <optional>

#include "../JuceLibraryCode/JuceHeader.h"
#include "MONSTRLookAndFeel.h"
#include "PluginProcessor.h"
#include "ParameterData.h"
#include "General/CoreMath.h"

class MONSTRCrossoverComponent : public Component {
public:

    MONSTRCrossoverComponent(MonstrAudioProcessor* newAudioProcessor);
    virtual ~MONSTRCrossoverComponent();

    void paint(Graphics& g) override;

    void mouseDown(const MouseEvent& event) override;

    void mouseDrag(const MouseEvent& event) override;

    void mouseUp(const MouseEvent& event) override;

    void mouseDoubleClick(const MouseEvent& event) override;

private:
    // The radius is used for drawing, and the target width for mouse events
    constexpr static int SLIDER_THUMB_RADIUS {6};
    constexpr static int SLIDER_THUMB_TARGET_WIDTH {SLIDER_THUMB_RADIUS * 2};

    std::array<double, 200>sineWaveTable;

    static const Colour lightGrey,
                        darkGrey,
                        lightGreyTrans;

    MonstrAudioProcessor* _processor;

    std::optional<std::function<void(const MouseEvent&)>> _mouseDragCallback;

    void _drawNeutralLine(Graphics& g);

    void _drawSine(Graphics& g);

    void _drawSliderThumbs(Graphics& g);

    void _drawWidthRectangles(Graphics& g);

    void _drawFrequencyText(Graphics& g);
};
