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
        : _processor(newAudioProcessor) {
}

MONSTRCrossoverMouseListener::~MONSTRCrossoverMouseListener() {
}

void MONSTRCrossoverMouseListener::mouseDown(const MouseEvent& event) {

    const int mouseDownX {event.getMouseDownX()};

    // For each available band, check if the cursor landed on a crossover frequency handle or on
    // the gaps in between
    const int numBands {_processor->numBands->get()};
    for (size_t bandIndex {0}; bandIndex < numBands; bandIndex++) {
        const double crossoverXPos {UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), event.eventComponent->getWidth())};

        if (mouseDownX < crossoverXPos - UIUtils::SLIDER_THUMB_TARGET_WIDTH) {

            // Drag started below a crossover handle, so is a width change
            _mouseDragCallback = [bandIndex, this](const MouseEvent& event) {
                _processor->setBandWidth(bandIndex, UIUtils::YPosToWidthValue(event.getPosition().getY(), event.eventComponent->getHeight()));
            };

            break;

        } else if (mouseDownX < crossoverXPos + UIUtils::SLIDER_THUMB_TARGET_WIDTH) {

            // Drag started on a crossover handle, so is a frequency change
            _mouseDragCallback = [bandIndex, this](const MouseEvent& event) {
                _processor->setCrossoverFrequency(bandIndex, UIUtils::XPosToSliderValue(event.getPosition().getX(), event.eventComponent->getWidth()));
            };

            break;
        }
    }

    // Handle the case for the highest band of the component in the furthest right
    const double topCrossoverXPos {UIUtils::sliderValueToXPos(_processor->crossoverParameters[numBands - 1]->get(), event.eventComponent->getWidth())};

    if (mouseDownX > topCrossoverXPos + UIUtils::SLIDER_THUMB_TARGET_WIDTH) {
        _mouseDragCallback = [&](const MouseEvent& event) {
            _processor->setBandWidth(numBands - 1, UIUtils::YPosToWidthValue(event.getPosition().getY(), event.eventComponent->getHeight()));
        };
    }
}

void MONSTRCrossoverMouseListener::mouseDrag(const MouseEvent& event) {

    if (_mouseDragCallback.has_value()) {
        (*_mouseDragCallback)(event);
    }
}

void MONSTRCrossoverMouseListener::mouseUp(const MouseEvent& event) {
    _mouseDragCallback.reset();
}

void MONSTRCrossoverMouseListener::mouseDoubleClick(const MouseEvent& event) {

    // This implements "double click to default" for the width parameters

    const int mouseDownX {event.getMouseDownX()};

    const double defaultWidth {
        WECore::StereoWidth::Parameters::WIDTH.InternalToNormalised(WECore::StereoWidth::Parameters::WIDTH.defaultValue)
    };

    // For each available band, check if the cursor landed on a crossover frequency handle or on
    // the gaps in between
    const int numBands {_processor->numBands->get()};
    for (size_t bandIndex {0}; bandIndex < numBands; bandIndex++) {
        const double crossoverXPos {UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), event.eventComponent->getWidth())};

        if (mouseDownX < crossoverXPos - UIUtils::SLIDER_THUMB_TARGET_WIDTH) {
            // Click landed below a crossover handle, so reset the width to its default
            _processor->setBandWidth(bandIndex, defaultWidth);
            break;

        } else if (mouseDownX < crossoverXPos + UIUtils::SLIDER_THUMB_TARGET_WIDTH) {
            // Drag started on a crossover handle - do nothing and exit the loop
            break;
        }
    }

    // We need to do one final check for if the cursor landed in the top band, above the highest
    // crossover
    const double topCrossoverXPos {UIUtils::sliderValueToXPos(_processor->crossoverParameters[numBands - 1]->get(), event.eventComponent->getWidth())};
    if (mouseDownX > topCrossoverXPos + UIUtils::SLIDER_THUMB_TARGET_WIDTH) {
        _processor->setBandWidth(numBands - 1, defaultWidth);
    }
}
