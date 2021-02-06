/*
 *	File:		MONSTRCrossoverWrapperComponent.cpp
 *
 *	Version:	1.0.0
 *
 *	Created:	06/02/2021
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

#include "MONSTRCrossoverWrapperComponent.h"

MONSTRCrossoverWrapperComponent::MONSTRCrossoverWrapperComponent(
        MonstrAudioProcessor* processor) {

    _parameterComponent.reset(new MONSTRCrossoverParameterComponent(processor));
    addAndMakeVisible(_parameterComponent.get());

    _imagerComponent.reset(new MONSTRCrossoverImagerComponent(processor));
    addAndMakeVisible(_imagerComponent.get());
    _imagerComponent->toBack();

    _mouseListener = std::make_unique<MONSTRCrossoverMouseListener>(processor);
    _parameterComponent->addMouseListener(_mouseListener.get(), false);
}

void MONSTRCrossoverWrapperComponent::resized() {
    _parameterComponent->setBounds(getLocalBounds());
    _imagerComponent->setBounds(getLocalBounds());
}

void MONSTRCrossoverWrapperComponent::start(MONSTRWidthLabel* widthValueLabel) {
    _mouseListener->start(widthValueLabel);
}

void MONSTRCrossoverWrapperComponent::stop() {
    _mouseListener->stop();
}

void MONSTRCrossoverWrapperComponent::onImagerUpdate() {
    _imagerComponent->repaint();
}

void MONSTRCrossoverWrapperComponent::onParameterUpdate() {
    _parameterComponent->repaint();
}
