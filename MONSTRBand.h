/*
 *	File:		MONSTRBand.h
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

#ifndef MONSTRBAND_H_INCLUDED
#define MONSTRBAND_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterData.h"

class MONSTRBand {
public:
    MONSTRBand(bool newIsLower, bool newIsUpper);
    ~MONSTRBand();
    
    void setLowCutoff(float val);
    void setHighCutoff(float val);
    void setWidth(float val);
    void setIsActive(bool val);
    
    void setSampleRate(double newSampleRate);
    
    float getLowCutoff() const;
    float getHighCutoff() const;
    float getWidth() const;
    float getIsActive() const;
    
    void makeBandLower();
    void makeBandMiddle();
    void makeBandUpper();
    
    void reset();
    
    void process2in2out(float* inLeftSamples, float* inRightSamples, int numSamples);
    
private:
    bool    isActive,
            isLower,
            isUpper;
    
    float   width,
            lowCutoff,
            highCutoff;
    
    int sampleRate;
    
    IIRFilter   lowCutLeft,
                lowCutRight,
                highCutLeft,
                highCutRight;
    
    template <typename T>
    T boundsCheck(T param, T min, T max) {
        if (param < min) param = min;
        if (param > max) param = max;
        
        return param;
    }
    
};



#endif  // MONSTRBAND_H_INCLUDED
