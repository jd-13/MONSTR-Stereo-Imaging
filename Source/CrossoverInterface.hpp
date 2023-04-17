#pragma once

#include <JuceHeader.h>
#include "CrossoverState.hpp"
#include "General/AudioSpinMutex.h"

namespace CrossoverInterface {
    struct Crossover {
        // Internal representation of the crossover
        std::shared_ptr<CrossoverState> state;

        // This mutex must be locked by all mutators before attempting to read or write to or from
        // data model. Its purpose is to stop a mutator being called on one thread from changing the
        // data model in a way that would crash a mutator being called on another thread.
        //
        // Recursive because the application code may call something via the mutator forEach methods
        // that tries to take the lock on the same thread as the forEach method itself
        std::recursive_mutex mutatorsMutex;

        // This mutex must be locked by mutators which change the structure of the data model, and
        // also by the processors. Its purpose is to stop a mutator being called on one thread from
        // changing the data model in a way that would crash a processor being called on another
        // thread.
        //
        // Mutators reading from the data model or writing only primitive values don't need to lock
        // this
        WECore::AudioSpinMutex sharedMutex;

        Crossover() : state(createDefaultCrossoverState()) {}
    };

    // Mutators
    void setIsBypassed(Crossover& crossover, size_t bandNumber, bool isBypassed);
    void setIsMuted(Crossover& crossover, size_t bandNumber, bool isMuted);
    void setIsSoloed(Crossover& crossover, size_t bandNumber, bool isSoloed);
    bool setCrossoverFrequency(Crossover& crossover, size_t crossoverNumber, double val);
    void setWidth(Crossover& crossover, size_t bandNumber, float val);

    bool getIsBypassed(Crossover& crossover, size_t bandNumber);
    bool getIsMuted(Crossover& crossover, size_t bandNumber);
    bool getIsSoloed(Crossover& crossover, size_t bandNumber);
    double getCrossoverFrequency(Crossover& crossover, size_t crossoverNumber);
    float getWidth(Crossover& crossover, size_t bandNumber);
    std::vector<double> getWidthMeterValues(Crossover& crossover);
    size_t getNumBands(Crossover& crossover);

    void addBand(Crossover& crossover);
    void removeBand(Crossover& crossover);

    void forEachBand(Crossover& crossover, std::function<void(int)> callback);
    void forEachCrossover(Crossover& crossover, std::function<void(int, double)> callback);

    // Processors
    void prepareToPlay(Crossover& crossover, double sampleRate, int samplesPerBlock);
    void reset(Crossover& crossover);
    void processBlock(Crossover& crossover, juce::AudioBuffer<float>& buffer);
}