/*
 *	File:		MONSTRBandProcessor.cpp
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

#include "MONSTRBandProcessor.h"

MONSTRBandProcessor::MONSTRBandProcessor() {
    // The envelope follower parameters are tuned to provide a useful output for the UI to draw
    _env.setAttackTimeMs(200);
    _env.setReleaseTimeMs(500);
}

void MONSTRBandProcessor::process2in2out(float* inSamplesLeft,
                                         float* inSamplesRight,
                                         size_t numSamples) {
    // Do processing
    WECore::StereoWidth::StereoWidthProcessor<float>::process2in2out(inSamplesLeft, inSamplesRight, numSamples);

    // Calculate the value the UI will use
    _updateWidthCache(inSamplesLeft, inSamplesRight, numSamples);
}

void MONSTRBandProcessor::setSampleRate(double val) {
    _env.setSampleRate(val);
    _env.reset();
}

void MONSTRBandProcessor::_updateWidthCache(float* inSamplesLeft,
                                            float* inSamplesRight,
                                            size_t numSamples) {

    // Take the difference of the samples and smooth the result with an envelope follower
    for (size_t index {0}; index < numSamples; index++) {
        _env.getNextOutput(inSamplesLeft[index] - inSamplesRight[index]);
    }
}
