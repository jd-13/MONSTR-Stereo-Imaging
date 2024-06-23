#include "CrossoverProcessors.hpp"

namespace {
    void processBand(BandState& band, juce::AudioBuffer<float>& buffer) {
        if (band.isMuted) {
            buffer.clear();
        } else {
            float* leftSamples {buffer.getWritePointer(0)};
            float* rightSamples {buffer.getWritePointer(1)};

            // Do the processing
            if (!band.isBypassed) {
                for (size_t index {0}; index < buffer.getNumSamples(); index++) {
                    const double mid {(leftSamples[index] + rightSamples[index]) * 0.5};
                    const double side {(rightSamples[index] - leftSamples[index]) * (band.width / 2)};

                    leftSamples[index] = mid - side;
                    rightSamples[index] = mid + side;
                }
            }

            // Update the envelope
            for (size_t index {0}; index < buffer.getNumSamples(); index++) {
                band.env->getNextOutput(leftSamples[index] - rightSamples[index]);
            }
        }
    }
}

namespace CrossoverProcessors {
    void prepareToPlay(CrossoverState& state, double sampleRate, int samplesPerBlock) {
        // We don't filter sidechain channels but do copy them to each buffer - so filters may need less channels than the buffers do
        for (juce::dsp::LinkwitzRileyFilter<float>& filter : state.lowpassFilters) {
            filter.prepare({sampleRate, static_cast<juce::uint32>(samplesPerBlock), static_cast<juce::uint32>(2)});
        }

        for (juce::dsp::LinkwitzRileyFilter<float>& filter : state.highpassFilters) {
            filter.prepare({sampleRate, static_cast<juce::uint32>(samplesPerBlock), static_cast<juce::uint32>(2)});
        }

        for (juce::dsp::LinkwitzRileyFilter<float>& filter : state.allpassFilters) {
            filter.prepare({sampleRate, static_cast<juce::uint32>(samplesPerBlock), static_cast<juce::uint32>(2)});
        }

        for (juce::AudioBuffer<float>& buffer : state.buffers) {
            buffer.setSize(2, samplesPerBlock);
        }

        for (BandState& band : state.bands) {
            band.env->setSampleRate(sampleRate);
        }

        state.sampleRate = sampleRate;
        state.samplesPerBlock = samplesPerBlock;
    }

    void reset(CrossoverState& state) {
        for (juce::dsp::LinkwitzRileyFilter<float>& filter : state.lowpassFilters) {
            filter.reset();
        }

        for (juce::dsp::LinkwitzRileyFilter<float>& filter : state.highpassFilters) {
            filter.reset();
        }

        for (juce::dsp::LinkwitzRileyFilter<float>& filter : state.allpassFilters) {
            filter.reset();
        }

        for (juce::AudioBuffer<float>& buffer : state.buffers) {
            buffer.clear();
        }

        for (BandState& band : state.bands) {
            band.env->reset();
        }
    }

    void processBlock(CrossoverState& state, juce::AudioBuffer<float>& buffer) {
        const size_t numCrossovers {state.bands.size() - 1};

        // First split everything into bands and apply the processing
        for (int crossoverNumber {0}; crossoverNumber < numCrossovers; crossoverNumber++) {
            // We need to make a copy of the input buffer before processing
            // lowBuffer will be lowpassed, highBuffer will be highpassed
            juce::AudioBuffer<float>& lowBuffer = crossoverNumber == 0 ? buffer : state.buffers[crossoverNumber - 1];
            juce::AudioBuffer<float>& highBuffer = state.buffers[crossoverNumber];

            highBuffer.makeCopyOf(lowBuffer);

            {
                juce::dsp::AudioBlock<float> block(juce::dsp::AudioBlock<float>(lowBuffer).getSubsetChannelBlock(0, 2));
                juce::dsp::ProcessContextReplacing context(block);
                state.lowpassFilters[crossoverNumber].process(context);

                // Crop the internal buffer in case the DAW has provided a buffer smaller than the specified block size in prepareToPlay
                juce::AudioBuffer<float> lowBufferCropped(lowBuffer.getArrayOfWritePointers(), lowBuffer.getNumChannels(), buffer.getNumSamples());
                processBand(state.bands[crossoverNumber], lowBufferCropped);
            }

            {
                juce::dsp::AudioBlock<float> block(juce::dsp::AudioBlock<float>(highBuffer).getSubsetChannelBlock(0, 2));
                juce::dsp::ProcessContextReplacing context(block);
                state.highpassFilters[crossoverNumber].process(context);

                // If this is the last band we need to apply the processing
                if (crossoverNumber + 1 == numCrossovers) {
                    // Crop the internal buffer in case the DAW has provided a buffer smaller than the specified block size in prepareToPlay
                    juce::AudioBuffer<float> highBufferCropped(highBuffer.getArrayOfWritePointers(), highBuffer.getNumChannels(), buffer.getNumSamples());
                    processBand(state.bands[crossoverNumber + 1], highBufferCropped);
                }
            }
        }

        // Finally add the bands back together
        if (state.numBandsSoloed > 0 && !state.bands[0].isSoloed) {
            buffer.clear();
        }

        for (int crossoverNumber {0}; crossoverNumber < numCrossovers; crossoverNumber++) {
            // If there is another crossover after this one, we need to use an allpass to rotate the phase of the lower bands
            if (crossoverNumber + 1 < numCrossovers) {
                juce::dsp::AudioBlock<float> block(juce::dsp::AudioBlock<float>(buffer).getSubsetChannelBlock(0, 2));
                juce::dsp::ProcessContextReplacing context(block);
                state.allpassFilters[crossoverNumber].process(context);
            }

            if (state.numBandsSoloed == 0 || state.bands[crossoverNumber + 1].isSoloed) {
                for (int channelNumber {0}; channelNumber < 2; channelNumber++) {
                    buffer.addFrom(channelNumber, 0, state.buffers[crossoverNumber], channelNumber, 0, buffer.getNumSamples());
                }
            }
        }
    }
}
