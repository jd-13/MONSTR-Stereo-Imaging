/*
 *	File:		MONSTR.cpp
 *
 *	Version:	1.0.0
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
#include <algorithm>


MONSTR::MONSTR() {}

MONSTR::~MONSTR() {}

void MONSTR::Process2in2out(float* leftSample, float* rightSample, size_t numSamples) {
    mCrossover.Process2in2out(leftSample, rightSample, numSamples);
}

void MONSTR::setSampleRate(double newSampleRate) {
    mCrossover.setSampleRate(newSampleRate);
}
