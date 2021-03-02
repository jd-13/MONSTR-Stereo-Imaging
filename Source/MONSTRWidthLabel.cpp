/*
 *	File:		MONSTRWidthLabel.cpp
 *
 *	Created:	30/01/2021
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

#include "MONSTRWidthLabel.h"

namespace {
    double widthValueToLabelValue(double value) {
        return value * 2 - 1;
    }
}

MONSTRWidthLabel::MONSTRWidthLabel(const String& componentName, const String& labelText) :
        _targetParameter(nullptr) {
}

void MONSTRWidthLabel::refreshValue() {

    String newValue("");

    // Check if there is a parameter to retrieve a value from
    if (_targetParameter != nullptr) {
        newValue = String(widthValueToLabelValue(_targetParameter->get()), 2);
    }

    // If the value has changed redraw the component
    if (_lastValue != newValue) {

        setText(newValue, dontSendNotification);
        _lastValue = newValue;

        repaint();
    }
}

void MONSTRWidthLabel::setTargetParameter(AudioParameterFloat* parameter) {
    _targetParameter = parameter;
};

void MONSTRWidthLabel::stop() {
    _targetParameter = nullptr;
}
