/*
  ==============================================================================

    MONSTR.h
    Created: 21 Jan 2016 9:53:21pm
    Author:  Jack Devlin

  ==============================================================================
*/

#ifndef MONSTR_H_INCLUDED
#define MONSTR_H_INCLUDED

#include "MONSTRBand.h"
#include "../JuceLibraryCode/JuceHeader.h"

class MONSTR {
public:
    MONSTR();
    ~MONSTR();
        
    MONSTRBand  band1,
                band2,
                band3;
    
    /* ClockProcess2in2out
     *
     * Performs the effect processing on inLeftSample and inRightSample. Use for
     * stereo in->stereo out signals.
     *
     * args: inLeftSample    Pointer to the left sample to be processed
     *       inRightSample   Pointer to the right sample to be processed
     *       numSamples      Number of samples loaded into the buffer
     */
    void ClockProcess(float* leftSample, float* rightSample, size_t numSamples);
    
    void setSampleRate(double newSampleRate);
    
    
private:    
};



#endif  // MONSTR_H_INCLUDED
