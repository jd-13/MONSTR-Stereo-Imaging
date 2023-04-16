#pragma once

#include "CrossoverState.hpp"

namespace CrossoverMutators {
    void setIsBypassed(std::shared_ptr<CrossoverState> state, size_t bandNumber, bool isBypassed);
    void setIsMuted(std::shared_ptr<CrossoverState> state, size_t bandNumber, bool isMuted);
    void setIsSoloed(std::shared_ptr<CrossoverState> state, size_t bandNumber, bool isSoloed);
    void setCrossoverFrequency(std::shared_ptr<CrossoverState> state, size_t crossoverNumber, double val);
    void setWidth(std::shared_ptr<CrossoverState> state, size_t bandNumber, float val);

    bool getIsBypassed(std::shared_ptr<CrossoverState> state, size_t bandNumber);
    bool getIsMuted(std::shared_ptr<CrossoverState> state, size_t bandNumber);
    bool getIsSoloed(std::shared_ptr<CrossoverState> state, size_t bandNumber);
    double getCrossoverFrequency(std::shared_ptr<CrossoverState> state, size_t crossoverNumber);
    float getWidth(std::shared_ptr<CrossoverState> state, size_t bandNumber);
    size_t getNumBands(std::shared_ptr<CrossoverState> state);

    void addBand(std::shared_ptr<CrossoverState> state);
    void removeBand(std::shared_ptr<CrossoverState> state, size_t bandNumber);
}
