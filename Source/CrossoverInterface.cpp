#include "CrossoverInterface.hpp"
#include "CrossoverMutators.hpp"
#include "CrossoverProcessors.hpp"

namespace CrossoverInterface {
    // Mutators
    void setIsBypassed(Crossover& crossover, size_t bandNumber, bool isBypassed) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            CrossoverMutators::setIsBypassed(crossover.state, bandNumber, isBypassed);
        }
    }

    void setIsMuted(Crossover& crossover, size_t bandNumber, bool isMuted) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            CrossoverMutators::setIsMuted(crossover.state, bandNumber, isMuted);
        }
    }

    void setIsSoloed(Crossover& crossover, size_t bandNumber, bool isSoloed) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            CrossoverMutators::setIsSoloed(crossover.state, bandNumber, isSoloed);
        }
    }

    bool setCrossoverFrequency(Crossover& crossover, size_t crossoverNumber, double val) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            return CrossoverMutators::setCrossoverFrequency(crossover.state, crossoverNumber, val);
        }

        return false;
    }

    void setWidth(Crossover& crossover, size_t bandNumber, float val) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            CrossoverMutators::setWidth(crossover.state, bandNumber, val);
        }
    }

    bool getIsBypassed(Crossover& crossover, size_t bandNumber) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            return CrossoverMutators::getIsBypassed(crossover.state, bandNumber);
        }

        return false;
    }

    bool getIsMuted(Crossover& crossover, size_t bandNumber) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            return CrossoverMutators::getIsMuted(crossover.state, bandNumber);
        }

        return false;
    }

    bool getIsSoloed(Crossover& crossover, size_t bandNumber) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            return CrossoverMutators::getIsSoloed(crossover.state, bandNumber);
        }

        return false;
    }

    double getCrossoverFrequency(Crossover& crossover, size_t crossoverNumber) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            return CrossoverMutators::getCrossoverFrequency(crossover.state, crossoverNumber);
        }

        return 0.0f;
    }

    float getWidth(Crossover& crossover, size_t bandNumber) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            return CrossoverMutators::getWidth(crossover.state, bandNumber);
        }

        return 0.0f;
    }

    std::vector<double> getWidthMeterValues(Crossover& crossover) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            return CrossoverMutators::getWidthMeterValues(crossover.state);
        }

        return std::vector<double>();
    }

    size_t getNumBands(Crossover& crossover) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            return CrossoverMutators::getNumBands(crossover.state);
        }

        return 0;
    }

    void addBand(Crossover& crossover) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        WECore::AudioSpinLock sharedLock(crossover.sharedMutex);

        if (crossover.state != nullptr) {
            CrossoverMutators::addBand(crossover.state);
        }
    }

    void removeBand(Crossover& crossover) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        WECore::AudioSpinLock sharedLock(crossover.sharedMutex);

        if (crossover.state != nullptr) {
            CrossoverMutators::removeBand(crossover.state, CrossoverMutators::getNumBands(crossover.state) - 1);
        }
    }

    void forEachBand(Crossover& crossover, std::function<void(int)> callback) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            for (int bandNumber {0}; bandNumber < CrossoverMutators::getNumBands(crossover.state); bandNumber++) {
                callback(bandNumber);
            }
        }
    }

    void forEachCrossover(Crossover& crossover, std::function<void(int, double)> callback) {
        std::scoped_lock lock(crossover.mutatorsMutex);
        if (crossover.state != nullptr) {
            for (int crossoverNumber {0}; crossoverNumber < CrossoverMutators::getNumBands(crossover.state) - 1; crossoverNumber++) {
                callback(crossoverNumber, CrossoverMutators::getCrossoverFrequency(crossover.state, crossoverNumber));
            }
        }
    }

    // Processors
    void prepareToPlay(Crossover& crossover, double sampleRate, int samplesPerBlock) {
        WECore::AudioSpinLock lock(crossover.sharedMutex);
        if (crossover.state != nullptr) {
            CrossoverProcessors::prepareToPlay(*crossover.state.get(), sampleRate, samplesPerBlock);
        }
    }

    void reset(Crossover& crossover) {
        WECore::AudioSpinLock lock(crossover.sharedMutex);
        if (crossover.state != nullptr) {
            CrossoverProcessors::reset(*crossover.state.get());
        }
    }

    void processBlock(Crossover& crossover, juce::AudioBuffer<float>& buffer) {
        // Use the try lock on the audio thread
        WECore::AudioSpinTryLock lock(crossover.sharedMutex);
        if (lock.isLocked() && crossover.state != nullptr) {
            CrossoverProcessors::processBlock(*crossover.state.get(), buffer);
        }
    }
}