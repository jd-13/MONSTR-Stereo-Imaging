/*
  ==============================================================================

    MONSTR.cpp
    Created: 21 Jan 2016 9:53:21pm
    Author:  Jack Devlin

  ==============================================================================
*/

#include "MONSTR.h"

MONSTR::MONSTR() :  band1(true, false),
                    band2(false, false),
                    band3(false, true) {
}

MONSTR::~MONSTR() {
    
}

void MONSTR::ClockProcess(float* leftSample, float* rightSample, int numSamples) {
    // make a copy of the buffers for each band to process in parallel
    float band1LeftBuffer[numSamples];
    float band1RightBuffer[numSamples];
    float band2LeftBuffer[numSamples];
    float band2RightBuffer[numSamples];
    float band3LeftBuffer[numSamples];
    float band3RightBuffer[numSamples];
    
    for (int iii {0}; iii < numSamples; iii++) {
        band1LeftBuffer[iii] = leftSample[iii];
        band2LeftBuffer[iii] = leftSample[iii];
        band3LeftBuffer[iii] = leftSample[iii];
        
        band1RightBuffer[iii] = rightSample[iii];
        band2RightBuffer[iii] = rightSample[iii];
        band3RightBuffer[iii] = rightSample[iii];
    }
    
    // let each band do its processing
    band1.process2in2out(&band1LeftBuffer[0], &band1RightBuffer[0], numSamples);
    
    // combine the output from each band, and write to output
    for (int iii {0}; iii < numSamples; iii++) {
        leftSample[iii] = band1LeftBuffer[iii];
        rightSample[iii] = band1RightBuffer[iii];
    }
}

void MONSTR::setSampleRate(double newSampleRate) {
    band1.setSampleRate(newSampleRate);
    band2.setSampleRate(newSampleRate);
    band3.setSampleRate(newSampleRate);
}