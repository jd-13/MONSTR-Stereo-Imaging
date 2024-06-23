#pragma once

#include <JuceHeader.h>
#include "MONSTRFilters/MONSTRParameters.h"
#include "WEFilters/AREnvelopeFollowerSquareLaw.h"
#include "WEFilters/StereoWidthProcessorParameters.h"

struct BandState {
    bool isBypassed;
    bool isMuted;
    bool isSoloed;
    float width;

    std::unique_ptr<WECore::AREnv::AREnvelopeFollowerSquareLaw> env;

    BandState() : isBypassed(false),
                  isMuted(false),
                  isSoloed(false),
                  width(WECore::StereoWidth::Parameters::WIDTH.defaultValue),
                  env(std::make_unique<WECore::AREnv::AREnvelopeFollowerSquareLaw>()) {
        env->setAttackTimeMs(200);
        env->setReleaseTimeMs(500);
    }
};

class CrossoverState {
public:
    // Num low/highpass filters = num bands - 1 (= num crossovers)
    std::vector<juce::dsp::LinkwitzRileyFilter<float>> lowpassFilters;
    std::vector<juce::dsp::LinkwitzRileyFilter<float>> highpassFilters;

    // Num allpass filters = num bands - 2
    std::vector<juce::dsp::LinkwitzRileyFilter<float>> allpassFilters;

    // Num buffers = num bands - 1 (= num crossovers)
    std::vector<juce::AudioBuffer<float>> buffers;

    std::vector<BandState> bands;

    int numBandsSoloed;

    double sampleRate;
    int samplesPerBlock;

    CrossoverState() : numBandsSoloed(0), sampleRate(44100), samplesPerBlock(32) {}
};

inline std::shared_ptr<CrossoverState> createDefaultCrossoverState() {
    auto state = std::make_shared<CrossoverState>();

    state->lowpassFilters.emplace_back();
    state->lowpassFilters[0].setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
    state->lowpassFilters[0].setCutoffFrequency(WECore::MONSTR::Parameters::CROSSOVER_FREQUENCY.defaultValue);

    state->highpassFilters.emplace_back();
    state->highpassFilters[0].setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    state->highpassFilters[0].setCutoffFrequency(WECore::MONSTR::Parameters::CROSSOVER_FREQUENCY.defaultValue);

    state->buffers.emplace_back();

    state->bands.emplace_back();
    state->bands.emplace_back();

    return state;
}
