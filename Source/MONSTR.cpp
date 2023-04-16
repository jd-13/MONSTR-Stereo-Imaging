/*
 *	File:		MONSTR.cpp
 *
 *	Created:	21/01/2016
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

#include "MONSTR.h"
#include "CrossoverProcessors.hpp"

MONSTR::MONSTR() {
    crossoverState = createDefaultCrossoverState();
}

void MONSTR::Process2in2out(juce::AudioBuffer<float>& buffer) {
    CrossoverProcessors::processBlock(*crossoverState.get(), buffer);
}

void MONSTR::prepareToPlay(double sampleRate, int samplesPerBlock) {
    CrossoverProcessors::prepareToPlay(*crossoverState.get(), sampleRate, samplesPerBlock);
}

void MONSTR::reset() {
    CrossoverProcessors::reset(*crossoverState.get());
}
