/*
 *	File:		UIUtils.h
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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

namespace {
    // These are tuned experimentally to get the desired log curve and crossings close to 0,0 and 1,1.
    constexpr double LOG_SCALE {3.00043};
    constexpr double LOG_OFFSET_1 {0.001};
    constexpr double LOG_OFFSET_2 {3};
}

namespace UIUtils {
    // The radius is used for drawing, and the target width for mouse events
    constexpr int SLIDER_THUMB_RADIUS {6};
    constexpr int SLIDER_THUMB_TARGET_WIDTH {SLIDER_THUMB_RADIUS * 2};

    constexpr int BAND_BUTTON_WIDTH {20};
    constexpr int BAND_BUTTON_PADDING {4};

    const Colour lightGrey(200, 200, 200);
    const Colour darkGrey(107, 107, 107);
    const Colour lightGreyTrans(static_cast<uint8_t>(200), 200, 200, 0.5f);
    const Colour mainHighlight(135, 252, 2);
    const Colour transHighlight(static_cast<uint8_t>(135), 252, 2, 0.5f);
    const Colour imagerColour(static_cast<uint8_t>(255), 255, 255, 0.2f);

    /**
     * Maps a linear scaled value in the range 0:1 to a log scaled value in the same range.
     */
    inline double sliderValueToInternalLog(double sliderValue) {
        return std::pow(10, LOG_SCALE * sliderValue - LOG_OFFSET_2) - LOG_OFFSET_1;
    }

    /**
     * Maps a log scaled value in the range 0:1 to a linear scaled value in the same range.
     */
    inline double internalLogToSliderValue(double internalValue) {
        return (std::log10(internalValue + LOG_OFFSET_1) + LOG_OFFSET_2) / LOG_SCALE;
    }

    /**
     * Converts a crossover frequency value between 0 and 1 to an x coordinate.
     */
    inline double sliderValueToXPos(double sliderValue, int componentWidth) {
        const double MARGIN_PX {componentWidth * 0.05};
        const double realRange {componentWidth - 2 * MARGIN_PX};

        return (internalLogToSliderValue(sliderValue) * realRange) + MARGIN_PX;
    }

    /**
     * Converts an x coordinate to a crossover frequency parameter value between 0 and 1.
     */
    inline double XPosToSliderValue(int XPos, int componentWidth) {
        const double MARGIN_PX {componentWidth * 0.05};
        const double realRange {componentWidth - 2 * MARGIN_PX};

        return sliderValueToInternalLog(std::max(XPos - MARGIN_PX, 0.0) / realRange);
    }

    /**
     * Converts a y coordinate to a width parameter value between 0 and 1.
     */
    inline double YPosToWidthValue(int YPos, int componentHeight) {
        return 1 - std::min(std::max(0.0, YPos - componentHeight / 4.0) / (componentHeight / 2.0), 1.0);
    }

    /**
     * Returns a rectangle representing the position of a button for the given crossover position
     * and index.
     */
    inline Rectangle<float> getButtonBounds(double crossoverXPos, int index) {
        return Rectangle<float>(crossoverXPos - BAND_BUTTON_WIDTH - SLIDER_THUMB_RADIUS,
                                BAND_BUTTON_PADDING + index * (BAND_BUTTON_PADDING + BAND_BUTTON_WIDTH),
                                BAND_BUTTON_WIDTH,
                                BAND_BUTTON_WIDTH);
    }
}