/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"

#include "PluginEditor.h"
#include "WEFilters/StereoWidthProcessorParameters.h"

//==============================================================================
MonstrAudioProcessor::MonstrAudioProcessor()
{
    namespace MP = WECore::MONSTR::Parameters;
    namespace SP = WECore::StereoWidth::Parameters;

    registerParameter(isActiveBand1, SWITCHBAND1_STR, MP::BANDSWITCH_DEFAULT, [&](bool val) { setIsActiveBand1(val); });
    registerParameter(widthBand1, WIDTHBAND1_STR, &SP::WIDTH, SP::WIDTH.defaultValue, [&](float val) { setWidthBand1(val); });
    registerParameter(crossoverLower, CROSSOVERLOWER_STR, &MP::CROSSOVERLOWER, MP::CROSSOVERLOWER.defaultValue, [&](float val) { setCrossoverLower(val); });
    registerParameter(isActiveBand2, SWITCHBAND2_STR, MP::BANDSWITCH_DEFAULT, [&](bool val) { setIsActiveBand2(val); });
    registerParameter(widthBand2, WIDTHBAND2_STR, &SP::WIDTH, SP::WIDTH.defaultValue, [&](float val) { setWidthBand2(val); });
    registerParameter(crossoverUpper, CROSSOVERUPPER_STR, &MP::CROSSOVERUPPER, MP::CROSSOVERUPPER.defaultValue, [&](float val) { setCrossoverUpper(val); });
    registerParameter(isActiveBand3, SWITCHBAND3_STR, MP::BANDSWITCH_DEFAULT, [&](bool val) { setIsActiveBand3(val); });
    registerParameter(widthBand3, WIDTHBAND3_STR, &SP::WIDTH, SP::WIDTH.defaultValue, [&](float val) { setWidthBand3(val); });
}

MonstrAudioProcessor::~MonstrAudioProcessor()
{
}

//==============================================================================
const String MonstrAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

const String MonstrAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String MonstrAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool MonstrAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool MonstrAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool MonstrAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MonstrAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MonstrAudioProcessor::silenceInProducesSilenceOut() const
{
    return true;
}

double MonstrAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MonstrAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MonstrAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MonstrAudioProcessor::setCurrentProgram (int index)
{
}

const String MonstrAudioProcessor::getProgramName (int index)
{
    return String();
}

void MonstrAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MonstrAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    mMONSTR.mCrossover.reset();
    // initialisation that you need..
}

void MonstrAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void MonstrAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i) {
        buffer.clear (i, 0, buffer.getNumSamples());
    }

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    float* inLeftSample {buffer.getWritePointer(0)};
    float* inRightSample {buffer.getWritePointer(1)};

    mMONSTR.setSampleRate(getSampleRate());

    mMONSTR.Process2in2out(inLeftSample, inRightSample, buffer.getNumSamples());
}

//==============================================================================
bool MonstrAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MonstrAudioProcessor::createEditor()
{
    return new MonstrAudioProcessorEditor (*this);
}

//==============================================================================
void MonstrAudioProcessor::setIsActiveBand1(bool val) {
    mMONSTR.mCrossover.band1.setIsActive(val);
    isActiveBand1->setValueNotifyingHost(val);
}

void MonstrAudioProcessor::setWidthBand1(float val) {
    mMONSTR.processors[0]->setWidth(WECore::StereoWidth::Parameters::WIDTH.NormalisedToInternal(val));
    widthBand1->setValueNotifyingHost(val);
}

void MonstrAudioProcessor::setCrossoverLower(float val) {
    mMONSTR.mCrossover.setCrossoverLower(WECore::MONSTR::Parameters::CROSSOVERLOWER.NormalisedToInternal(val));
    crossoverLower->setValueNotifyingHost(val);
}

void MonstrAudioProcessor::setIsActiveBand2(bool val) {
    mMONSTR.mCrossover.band2.setIsActive(val);
    isActiveBand2->setValueNotifyingHost(val);
}

void MonstrAudioProcessor::setWidthBand2(float val) {
    mMONSTR.processors[1]->setWidth(WECore::StereoWidth::Parameters::WIDTH.NormalisedToInternal(val));
    widthBand2->setValueNotifyingHost(val);
}

void MonstrAudioProcessor::setCrossoverUpper(float val) {
    mMONSTR.mCrossover.setCrossoverUpper(WECore::MONSTR::Parameters::CROSSOVERUPPER.NormalisedToInternal(val));
    crossoverUpper->setValueNotifyingHost(val);
}

void MonstrAudioProcessor::setIsActiveBand3(bool val) {
    mMONSTR.mCrossover.band3.setIsActive(val);
    isActiveBand3->setValueNotifyingHost(val);
}

void MonstrAudioProcessor::setWidthBand3(float val) {
    mMONSTR.processors[2]->setWidth(WECore::StereoWidth::Parameters::WIDTH.NormalisedToInternal(val));
    widthBand3->setValueNotifyingHost(val);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MonstrAudioProcessor();
}
