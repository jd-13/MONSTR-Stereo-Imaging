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

namespace UIUtils {
    // The radius is used for drawing, and the target width for mouse events
    constexpr int SLIDER_THUMB_RADIUS {6};
    constexpr int SLIDER_THUMB_TARGET_WIDTH {SLIDER_THUMB_RADIUS * 2};

    constexpr int BAND_BUTTON_WIDTH {20};
    constexpr int BAND_BUTTON_PADDING {4};

    inline double sliderValueToInternalLog(double sliderValue) {
        return std::pow(10, 1.0414 * sliderValue - 1) - 0.1;
    }

    inline double internalLogToSliderValue(double internalValue) {
        return (std::log10(internalValue + 0.1) + 1) / 1.0414;
    }

    inline double sliderValueToXPos(double sliderValue, int componentWidth) {
        const double MARGIN_PX {componentWidth * 0.05};
        const double realRange {componentWidth - 2 * MARGIN_PX};

        return (internalLogToSliderValue(sliderValue) * realRange) + MARGIN_PX;
    }

    inline double XPosToSliderValue(int XPos, int componentWidth) {
        const double MARGIN_PX {componentWidth * 0.05};
        const double realRange {componentWidth - 2 * MARGIN_PX};

        return sliderValueToInternalLog(std::max(XPos - MARGIN_PX, 0.0) / realRange);
    }

    inline double YPosToWidthValue(int YPos, int componentHeight) {
        return 1 - std::min(std::max(0.0, YPos - componentHeight / 4.0) / (componentHeight / 2.0), 1.0);
    }
}