/*
 *	File:		MONSTRBand.cpp
 *
 *	Version:	0.01.00
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

#include "MONSTRBand.h"

MONSTRBand::MONSTRBand(bool newIsLower, bool newIsUpper) :
                            isBypassed(BANDSWITCH_DEFAULT),
                            width(WIDTH_DEFAULT),
                            lowCutoff(CROSSOVERLOWER_DEFAULT),
                            highCutoff(CROSSOVERUPPER_DEFAULT),
                            sampleRate(44100),
                            lowCutLeft(),
                            lowCutRight(),
                            highCutLeft(),
                            highCutRight(),
                            isLower(newIsLower),
                            isUpper(newIsUpper) {
    //assert(isLower != isUpper);
}



MONSTRBand::~MONSTRBand() {
}



void MONSTRBand::setLowCutoff(float val) {
    // TODO: add better bounds checks
    // if this is the lowest band, then do not cut the low frequencies
    if (!isLower && !isUpper) {
        lowCutoff = boundsCheck<float>(val, CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX);
        lowCutLeft.setCoefficients(IIRCoefficients::makeHighPass(sampleRate, lowCutoff));
        lowCutRight.setCoefficients(IIRCoefficients::makeHighPass(sampleRate, lowCutoff));
    } else if (isUpper) {
        lowCutoff = boundsCheck<float>(val, CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX);
        lowCutLeft.setCoefficients(IIRCoefficients::makeHighPass(sampleRate, lowCutoff));
        lowCutRight.setCoefficients(IIRCoefficients::makeHighPass(sampleRate, lowCutoff));
    }
}

void MONSTRBand::setHighCutoff(float val) {
    // if this is the highest band, then do not cut the high frequencies
    
    if (!isLower && !isUpper) {
        highCutoff = boundsCheck<float>(val, CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX);
        highCutLeft.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, highCutoff));
        highCutRight.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, highCutoff));
    } else if (isLower) {
        highCutoff = boundsCheck<float>(val, CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX);
        highCutLeft.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, highCutoff));
        highCutRight.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, highCutoff));
    }
}

void MONSTRBand::setWidth(float val) {
    width = boundsCheck<float>(val, WIDTH_MIN, WIDTH_MAX);
}

void MONSTRBand::setIsbypassed(bool val) {
    isBypassed = val;
}

void MONSTRBand::setSampleRate(double newSampleRate) {
    // if the new sample rate is different, recalculate the filter coefficients
    if (newSampleRate != sampleRate) {
        sampleRate = boundsCheck<double>(newSampleRate, 0, 192000); //TODO: confirm highest expected sample rate
        setLowCutoff(lowCutoff);
        setHighCutoff(highCutoff);
    }
}

float MONSTRBand::getLowCutoff() const {
    return lowCutoff;
}

float MONSTRBand::getHighCutoff() const {
    Logger::outputDebugString(__func__ + String(": ") + String(highCutoff));
    return highCutoff;
}

float MONSTRBand::getWidth() const {
    return width;
}

float MONSTRBand::getIsBypassed() const {
    return isBypassed;
}

void MONSTRBand::makeBandLower(bool val) {
    // lets the band know if it covers the lowest frequencies
    isLower = val;
    isUpper = !val;
}

void MONSTRBand::makeBandUpper(bool val) {
    // lets the band know if it covers the highest frequencies
    isLower = !val;
    isUpper = val;
}

void MONSTRBand::reset() {
    lowCutLeft.reset();
    lowCutRight.reset();
    highCutLeft.reset();
    highCutRight.reset();
}

void MONSTRBand::process2in2out(float* inLeftSamples, float* inRightSamples, int numSamples) {
    // add upper/lower bypass depending on isupper/islower
    
    highCutLeft.processSamples(inLeftSamples, numSamples);
    highCutRight.processSamples(inRightSamples, numSamples);
}


