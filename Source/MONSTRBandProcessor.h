/*
 *	File:		MONSTRBandProcessor.h
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

#pragma once

#include <array>

#include "WEFilters/StereoWidthProcessor.h"
#include "WEFilters/AREnvelopeFollowerSquareLaw.h"

/**
 * Performs stereo width processing but also calculates and caches the stereo width of the output.
 */
class MONSTRBandProcessor : public WECore::StereoWidth::StereoWidthProcessor<float> {
public:
    MONSTRBandProcessor();
    ~MONSTRBandProcessor() = default;

    virtual void process2in2out(float* inSamplesLeft,
                                float* inSamplesRight,
                                size_t numSamples) override;

    void setSampleRate(double val);

    double getProcessedWidthValue() const { return _env.getLastOutput(); }

private:
    WECore::AREnv::AREnvelopeFollowerSquareLaw _env;

    void _updateWidthCache(float* inSamplesLeft, float* inSamplesRight, size_t numSamples);
};
