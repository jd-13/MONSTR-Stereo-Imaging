/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterData.h"
#include "CoreJUCEPlugin/CoreAudioProcessor.h"
#include "CrossoverInterface.hpp"

//==============================================================================
/**
*/
class MonstrAudioProcessor  : public WECore::JUCEPlugin::CoreAudioProcessor
{
public:
    CrossoverInterface::Crossover crossover;

    //==============================================================================
    MonstrAudioProcessor();
    ~MonstrAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void reset() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    /**
     * Parameter setters.
     *
     * For float parameters a value in the internal parameter range is expected.
     *

     */
    /** @{ */
    void addBand();
    void removeBand();
    void setCrossoverFrequency(size_t index, float val);
    /** @} */

    struct BandParametersWrapper {
        AudioParameterBool* isActive;
        AudioParameterBool* isMuted;
        AudioParameterBool* isSoloed;
        AudioParameterFloat* width;
    };

    // Parameters (public for beginChangeGesture/endChangeGesture/get)
    AudioParameterInt* numBands;
    std::array<BandParametersWrapper, WECore::MONSTR::Parameters::_MAX_NUM_BANDS> bandParameters;
    std::array<AudioParameterFloat*, WECore::MONSTR::Parameters::_MAX_NUM_BANDS - 1> crossoverParameters;

private:
    void _refreshCrossoverParameters();

    std::vector<juce::String> _provideParamNamesForMigration() override;
    void _migrateParamValues(std::vector<float>& paramValues) override;

    void _onParameterUpdate() override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonstrAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
