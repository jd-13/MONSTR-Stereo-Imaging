/*
 *	File:		MONSTRWidthSlider.cpp
 *
 *	Version:	1.0.0
 *
 *	Created:	09/04/2016
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

#include "MONSTRWidthSlider.h"
MONSTRWidthSlider::MONSTRWidthSlider(String name, std::function<void(bool)> setParameterCallback)
        : Slider(name),
          _setParameterCallback(setParameterCallback) {
}

void MONSTRWidthSlider::mouseDown(const juce::MouseEvent &event) {
    if (event.mods.isRightButtonDown()) {
        setEnabled(!isEnabled());
        _setParameterCallback(isEnabled());
    }

    Slider::mouseDown(event);
}
