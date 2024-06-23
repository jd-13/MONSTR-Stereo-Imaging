/*
 *	File:		MONSTRCrossoverMouseListener.h
 *
 *	Created:	21/01/2021
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
#include <optional>

#include "../JuceLibraryCode/JuceHeader.h"
#include "MONSTRWidthLabel.h"
#include "PluginProcessor.h"
#include "ParameterData.h"

class MONSTRCrossoverMouseListener : public MouseListener {
public:

    MONSTRCrossoverMouseListener(MonstrAudioProcessor* newAudioProcessor);
    virtual ~MONSTRCrossoverMouseListener();

    void mouseMove(const MouseEvent& event) override;

    void mouseExit(const MouseEvent& event) override;

    void mouseDown(const MouseEvent& event) override;

    void mouseDrag(const MouseEvent& event) override;

    void mouseUp(const MouseEvent& event) override;

    void mouseDoubleClick(const MouseEvent& event) override;

    void start(MONSTRWidthLabel* widthValueLabel, juce::Label* tooltipLabel) {
        _widthValueLabel = widthValueLabel;
        _tooltipLabel = tooltipLabel;
    }

    void stop() {
        _widthValueLabel = nullptr;
        _tooltipLabel = nullptr;
    }

private:

    struct FloatParameterInteraction {
        std::function<void(const MouseEvent&)> dragCallback;
        std::function<void()> resetToDefault;
        std::function<void()> beginGesture;
        std::function<void()> endGesture;

        FloatParameterInteraction() :
            dragCallback([](const MouseEvent&) {}),
            resetToDefault([]() {}),
            beginGesture([]() {}),
            endGesture([]() {}) { }

        FloatParameterInteraction(
                std::function<void(const MouseEvent&)> newDragCallback,
                std::function<void()> newResetToDefault,
                std::function<void()> newBeginGesture,
                std::function<void()> newEndGesture) :
            dragCallback(newDragCallback),
            resetToDefault(newResetToDefault),
            beginGesture(newBeginGesture),
            endGesture(newEndGesture) { }
    };

    std::array<FloatParameterInteraction, WECore::MONSTR::Parameters::_MAX_NUM_BANDS> _bandWidths;
    std::array<FloatParameterInteraction, WECore::MONSTR::Parameters::_MAX_NUM_BANDS - 1> _crossoverFrequencies;

    MonstrAudioProcessor* _processor;

    FloatParameterInteraction _dragParameter;

    MONSTRWidthLabel* _widthValueLabel;

    juce::Label* _tooltipLabel;

    /**
     * If the mouse event occured inside a button the function will handle it and return null,
     * if the event occured inside a slider it will return the corresponding
     * FloatParameterInteraction for it to be handled by the appropriate event handlers.
     */
    FloatParameterInteraction _resolveParameterInteraction(const MouseEvent& event);

    void _updateWidthValueLabel(const MouseEvent& event);
    void _updateTooltip(const MouseEvent& event);
};
