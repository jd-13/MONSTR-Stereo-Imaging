/*
 *	File:		MONSTRCrossoverMouseListener.h
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

#include <memory>

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class MONSTRCrossoverMouseListener : public MouseListener {
public:

    MONSTRCrossoverMouseListener(MonstrAudioProcessor* newAudioProcessor);
    virtual ~MONSTRCrossoverMouseListener();

    void mouseDown(const MouseEvent& event) override;

    void mouseDrag(const MouseEvent& event) override;

    void mouseUp(const MouseEvent& event) override;

    void mouseDoubleClick(const MouseEvent& event) override;

private:
    MonstrAudioProcessor* _processor;

    std::optional<std::function<void(const MouseEvent&)>> _mouseDragCallback;
};
