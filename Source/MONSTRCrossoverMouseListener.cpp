/*
 *	File:		MONSTRCrossoverMouseListener.cpp
 *
 *	Version:	1.0.0
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

#include "MONSTRCrossoverComponent.h"

#include <algorithm>

#include "UIUtils.h"
#include "WEFilters/StereoWidthProcessorParameters.h"

MONSTRCrossoverMouseListener::MONSTRCrossoverMouseListener(MonstrAudioProcessor* newAudioProcessor)
        : _processor(newAudioProcessor),
          _dragParameter(nullptr) {

    // Initialise the parameter interactions

    const double defaultWidth {
        WECore::StereoWidth::Parameters::WIDTH.InternalToNormalised(WECore::StereoWidth::Parameters::WIDTH.defaultValue)
    };

    for (int bandIndex {0}; bandIndex < WECore::MONSTR::Parameters::NUM_BANDS.maxValue; bandIndex++) {

        _bandWidths[bandIndex] = {
            [bandIndex, defaultWidth, this](const MouseEvent& event) {
                _processor->setBandWidth(bandIndex, UIUtils::YPosToWidthValue(event.getPosition().getY(), event.eventComponent->getHeight()));
            },
            [bandIndex, defaultWidth, this]() { _processor->setBandWidth(bandIndex, defaultWidth); },
            [bandIndex, this]() { _processor->bandParameters[bandIndex].width->beginChangeGesture(); },
            [bandIndex, this]() { _processor->bandParameters[bandIndex].width->endChangeGesture(); }
        };
    }

    for (int bandIndex {0}; bandIndex < WECore::MONSTR::Parameters::NUM_BANDS.maxValue - 1; bandIndex++) {

        _crossoverFrequencies[bandIndex] = {
            [bandIndex, this](const MouseEvent& event) {
                _processor->setCrossoverFrequency(bandIndex, UIUtils::XPosToSliderValue(event.getPosition().getX(), event.eventComponent->getWidth()));
            },
            []() { /* Do nothing */ },
            [bandIndex, this]() { _processor->crossoverParameters[bandIndex]->beginChangeGesture(); },
            [bandIndex, this]() { _processor->crossoverParameters[bandIndex]->endChangeGesture(); }
        };

    }

}

MONSTRCrossoverMouseListener::~MONSTRCrossoverMouseListener() {
}

void MONSTRCrossoverMouseListener::mouseDown(const MouseEvent& event) {
    _dragParameter = _resolveParameterInteraction(event);

    if (_dragParameter != nullptr) {
        _dragParameter->beginGesture();
    }
}

void MONSTRCrossoverMouseListener::mouseDrag(const MouseEvent& event) {

    if (_dragParameter != nullptr) {
        _dragParameter->dragCallback(event);
    }
}

void MONSTRCrossoverMouseListener::mouseUp(const MouseEvent& event) {

    if (_dragParameter != nullptr) {
        _dragParameter->endGesture();
        _dragParameter = nullptr;
    }
}

void MONSTRCrossoverMouseListener::mouseDoubleClick(const MouseEvent& event) {

    // This implements "double click to default" for the width parameters
    FloatParameterInteraction* param {_resolveParameterInteraction(event)};

    if (param != nullptr) {
       param->resetToDefault();
    }
}

MONSTRCrossoverMouseListener::FloatParameterInteraction* MONSTRCrossoverMouseListener::_resolveParameterInteraction(const MouseEvent& event) {

    FloatParameterInteraction* retVal {nullptr};

    const int mouseDownX {event.getMouseDownX()};
    const int mouseDownY {event.getMouseDownY()};

    // For each available band, check if the cursor landed on a crossover frequency handle or on
    // the gaps in between
    const int numBands {_processor->numBands->get()};

    for (size_t bandIndex {0}; bandIndex < numBands; bandIndex++) {
        const double crossoverXPos {bandIndex < numBands - 1 ?
            UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), event.eventComponent->getWidth()) :
            event.eventComponent->getWidth()
        };

        const double buttonXPos {UIUtils::crossoverXPosToButtonXPos(crossoverXPos)};

        const bool isWithinButtonXRange {
            mouseDownX > buttonXPos && mouseDownX < buttonXPos + UIUtils::BAND_BUTTON_WIDTH
        };

        const bool isOnTopButton {
            isWithinButtonXRange &&
            mouseDownY > UIUtils::getButtonYPos(0) && mouseDownY < UIUtils::getButtonYPos(0) + UIUtils::BAND_BUTTON_WIDTH
        };

        const bool isOnMiddleButton {
            isWithinButtonXRange &&
            mouseDownY > UIUtils::getButtonYPos(1) && mouseDownY < UIUtils::getButtonYPos(1) + UIUtils::BAND_BUTTON_WIDTH
        };

        const bool isOnBottomButton {
            isWithinButtonXRange &&
            mouseDownY > UIUtils::getButtonYPos(2) && mouseDownY < UIUtils::getButtonYPos(2) + UIUtils::BAND_BUTTON_WIDTH
        };

        if (isOnTopButton) {
            // Landed on the bypass button
            _processor->setBandActive(bandIndex, !_processor->bandParameters[bandIndex].isActive->get());
            break;

        } else if (isOnMiddleButton) {
            // Landed on the mute button
            _processor->setBandMuted(bandIndex, !_processor->bandParameters[bandIndex].isMuted->get());
            break;

        } else if (isOnBottomButton) {
            // Landed on the solo button
            _processor->setBandSoloed(bandIndex, !_processor->bandParameters[bandIndex].isSoloed->get());
            break;

        } else if (mouseDownX < crossoverXPos - UIUtils::SLIDER_THUMB_TARGET_WIDTH) {
            // Click landed below a crossover handle but outside a button, so must be on the width
            retVal = &(_bandWidths[bandIndex]);
            break;

        } else if (mouseDownX < crossoverXPos + UIUtils::SLIDER_THUMB_TARGET_WIDTH) {
            // Click landed on a crossover handle
            retVal = &(_crossoverFrequencies[bandIndex]);
            break;
        }
    }

    return retVal;
}
