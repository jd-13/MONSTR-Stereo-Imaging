/*
 *	File:		MONSTRWidthSlider.h
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

#ifndef MONSTRWIDTHSLIDER_H_INCLUDED
#define MONSTRWIDTHSLIDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class MONSTRWidthSlider : public Slider {
public:
    MONSTRWidthSlider(String name, std::function<void(bool)> setParameterCallback);

    virtual void mouseDown(const MouseEvent& event) override;

private:
    std::function<void(bool)> _setParameterCallback;

};



#endif  // MONSTRWidthSlider_H_INCLUDED
