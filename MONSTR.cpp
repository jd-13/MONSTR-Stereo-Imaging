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

void MONSTR::ClockProcess(float* leftSample, float* rightSample, size_t numSamples) {
    // make a copy of the buffers for each band to process in parallel
    std::vector<float> band1LeftBuffer(numSamples);
    std::vector<float> band1RightBuffer(numSamples);
    std::vector<float> band2LeftBuffer(numSamples);
    std::vector<float> band2RightBuffer(numSamples);
    std::vector<float> band3LeftBuffer(numSamples);
    std::vector<float> band3RightBuffer(numSamples);
    
    for (size_t iii {0}; iii < numSamples; iii++) {
        band1LeftBuffer[iii] = leftSample[iii];
        band2LeftBuffer[iii] = leftSample[iii];
        band3LeftBuffer[iii] = leftSample[iii];
        
        band1RightBuffer[iii] = rightSample[iii];
        band2RightBuffer[iii] = rightSample[iii];
        band3RightBuffer[iii] = rightSample[iii];
    }
    
    // let each band do its processing
    band1.process2in2out(band1LeftBuffer, band1RightBuffer);
    band2.process2in2out(band2LeftBuffer, band2RightBuffer);
    band3.process2in2out(band3LeftBuffer, band3RightBuffer);
    
    // combine the output from each band, and write to output
    for (size_t iii {0}; iii < numSamples; iii++) {
        leftSample[iii] = band1LeftBuffer[iii] + band2LeftBuffer[iii] + band3LeftBuffer[iii];
        rightSample[iii] = band1RightBuffer[iii] + band2RightBuffer[iii] + band3RightBuffer[iii];
    }
}

void MONSTR::setSampleRate(double newSampleRate) {
    band1.setSampleRate(newSampleRate);
    band2.setSampleRate(newSampleRate);
    band3.setSampleRate(newSampleRate);
}