/*
 *	File:		MONSTR.h
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

#ifndef MONSTR_H_INCLUDED
#define MONSTR_H_INCLUDED

#include "MONSTRCrossover.h"
#include "../JuceLibraryCode/JuceHeader.h"

class MONSTR {
public:
    MONSTR();
    ~MONSTR();
    
    MONSTRCrossover mCrossover;
    
    /* Process2in2out
     *
     * Performs the effect processing on inLeftSample and inRightSample. Use for
     * stereo in->stereo out signals.
     *
     * args: inLeftSample    Pointer to the left sample to be processed
     *       inRightSample   Pointer to the right sample to be processed
     *       numSamples      Number of samples loaded into the buffer
     */
    void Process2in2out(float* leftSample, float* rightSample, size_t numSamples);
    
    void setSampleRate(double newSampleRate);
    
    
private:    
};



#endif  // MONSTR_H_INCLUDED
