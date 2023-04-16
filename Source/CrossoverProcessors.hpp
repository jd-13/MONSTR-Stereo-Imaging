#pragma once

#include "CrossoverState.hpp"

namespace CrossoverProcessors {
    void prepareToPlay(CrossoverState& state, double sampleRate, int samplesPerBlock);
    void reset(CrossoverState& state);
    void processBlock(CrossoverState& state, juce::AudioBuffer<float>& buffer);
}
