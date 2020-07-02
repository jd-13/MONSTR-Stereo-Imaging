/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MonstrAudioProcessor::MonstrAudioProcessor()
{
    mMONSTR.mCrossover.setCrossoverLower(WECore::MONSTR::Parameters::CROSSOVERLOWER.defaultValue);
    mMONSTR.mCrossover.setCrossoverUpper(WECore::MONSTR::Parameters::CROSSOVERUPPER.defaultValue);
    
    mMONSTR.mCrossover.band1.setWidth(WECore::MONSTR::Parameters::WIDTH.defaultValue);
    mMONSTR.mCrossover.band1.setIsActive(WECore::MONSTR::Parameters::BANDSWITCH_DEFAULT);
    
    mMONSTR.mCrossover.band2.setWidth(WECore::MONSTR::Parameters::WIDTH.defaultValue);
    mMONSTR.mCrossover.band2.setIsActive(WECore::MONSTR::Parameters::BANDSWITCH_DEFAULT);
    
    mMONSTR.mCrossover.band3.setWidth(WECore::MONSTR::Parameters::WIDTH.defaultValue);
    mMONSTR.mCrossover.band3.setIsActive(WECore::MONSTR::Parameters::BANDSWITCH_DEFAULT);
    
    UIUpdateFlag = true;
}

MonstrAudioProcessor::~MonstrAudioProcessor()
{
}

//==============================================================================
const String MonstrAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int MonstrAudioProcessor::getNumParameters()
{
    return totalNumParams;
}

float MonstrAudioProcessor::getParameter (int index)
{
    switch (index) {
        case isActiveBand1:
            return mMONSTR.mCrossover.band1.getIsActive();
            
        case widthBand1:
            return WECore::MONSTR::Parameters::WIDTH.InteralToNormalised(mMONSTR.mCrossover.band1.getWidth());
            
        
        
        case crossoverLower:
            return WECore::MONSTR::Parameters::CROSSOVERLOWER.InteralToNormalised(mMONSTR.mCrossover.getCrossoverLower());
            
        
        
        case isActiveBand2:
            return mMONSTR.mCrossover.band2.getIsActive();
            
        case widthBand2:
            return WECore::MONSTR::Parameters::WIDTH.InteralToNormalised(mMONSTR.mCrossover.band2.getWidth());
            
        
        
        case crossoverUpper:
            return WECore::MONSTR::Parameters::CROSSOVERUPPER.InteralToNormalised(mMONSTR.mCrossover.getCrossoverUpper());
            
        
        
        case isActiveBand3:
            return mMONSTR.mCrossover.band3.getIsActive();
            
        case widthBand3:
            return WECore::MONSTR::Parameters::WIDTH.InteralToNormalised(mMONSTR.mCrossover.band3.getWidth());
            
        
        
        default:
            return 0.0f;
    }
}

void MonstrAudioProcessor::setParameter (int index, float newValue)
{
    switch (index) {
        case isActiveBand1:
            mMONSTR.mCrossover.band1.setIsActive(newValue > 0.5);
            break;
            
        case widthBand1:
            mMONSTR.mCrossover.band1.setWidth(WECore::MONSTR::Parameters::WIDTH.NormalisedToInteral(newValue));
            break;
            
            
            
        case crossoverLower:
            mMONSTR.mCrossover.setCrossoverLower(WECore::MONSTR::Parameters::CROSSOVERLOWER.NormalisedToInteral(newValue));
            break;
            
            
            
        case isActiveBand2:
            mMONSTR.mCrossover.band2.setIsActive(newValue > 0.5);
            break;
            
        case widthBand2:
            mMONSTR.mCrossover.band2.setWidth(WECore::MONSTR::Parameters::WIDTH.NormalisedToInteral(newValue));
            break;
            
            
            
        case crossoverUpper:
            mMONSTR.mCrossover.setCrossoverUpper(WECore::MONSTR::Parameters::CROSSOVERUPPER.NormalisedToInteral(newValue));
            break;
            
            
            
        case isActiveBand3:
            mMONSTR.mCrossover.band3.setIsActive(newValue > 0.5);
            break;
            
        case widthBand3:
            mMONSTR.mCrossover.band3.setWidth(WECore::MONSTR::Parameters::WIDTH.NormalisedToInteral(newValue));
            
        default:
            break;
    }
}

const String MonstrAudioProcessor::getParameterName (int index)
{
    switch (index) {
        case isActiveBand1:
            return SWITCHBAND1_STR;
            
        case widthBand1:
            return WIDTHBAND1_STR;
            
            
            
        case crossoverLower:
            return CROSSOVERLOWER_STR;
            
            
            
        case isActiveBand2:
            return SWITCHBAND2_STR;
            
        case widthBand2:
            return WIDTHBAND2_STR;
            
            
            
        case crossoverUpper:
            return CROSSOVERUPPER_STR;
            
            
            
        case isActiveBand3:
            return SWITCHBAND3_STR;
            
        case widthBand3:
            return WIDTHBAND3_STR;
            
        default:
            return String::empty;
    }
}

const String MonstrAudioProcessor::getParameterText (int index)
{
    switch (index) {
        case isActiveBand1:
            return String(static_cast<int>(mMONSTR.mCrossover.band1.getIsActive()));
            
        case widthBand1:
            return String(WECore::MONSTR::Parameters::WIDTH.InteralToNormalised(mMONSTR.mCrossover.band1.getWidth()));
            
            
            
        case crossoverLower:
            return String(WECore::MONSTR::Parameters::CROSSOVERLOWER.InteralToNormalised(mMONSTR.mCrossover.getCrossoverLower()));
            
            
            
        case isActiveBand2:
            return String(static_cast<int>(mMONSTR.mCrossover.band2.getIsActive()));
            
        case widthBand2:
            return String(WECore::MONSTR::Parameters::WIDTH.InteralToNormalised(mMONSTR.mCrossover.band2.getWidth()));
            
            
            
        case crossoverUpper:
            return String(WECore::MONSTR::Parameters::CROSSOVERUPPER.InteralToNormalised(mMONSTR.mCrossover.getCrossoverUpper()));
            
            
            
        case isActiveBand3:
            return String(static_cast<int>(mMONSTR.mCrossover.band3.getIsActive()));
            
        case widthBand3:
            return String(WECore::MONSTR::Parameters::WIDTH.InteralToNormalised(mMONSTR.mCrossover.band3.getWidth()));
            
        default:
            return String::empty;
    }
}

bool MonstrAudioProcessor::isParameterAutomatable(int parameterIndex) const {
    switch (parameterIndex) {
        case isActiveBand1:
        case isActiveBand2:
        case isActiveBand3:
            return false;
            
        default:
            return true;
    }
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
void MonstrAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    std::vector<float> userParams;
    for (int iii {0}; iii < totalNumParams; iii++) {
        userParams.push_back(getParameter(iii));
    }
    
    XmlElement root("Root");
    XmlElement *el = root.createNewChildElement("AllUserParam");
    
    el->addTextElement(String(floatVectorToString(userParams)));
    copyXmlToBinary(root, destData);
}

void MonstrAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> pRoot(getXmlFromBinary(data, sizeInBytes));
    std::vector<float> tmpUserParam;
    
    if (pRoot != NULL) {
        forEachXmlChildElement((*pRoot), pChild) {
            if (pChild->hasTagName("AllUserParam")) {
                String sFloatCSV = pChild->getAllSubText();
                if (stringToFloatVector(sFloatCSV, tmpUserParam, totalNumParams) == totalNumParams) {
                    for (int iii {0}; iii < totalNumParams; iii++) {
                        setParameter(iii, tmpUserParam[iii]);
                    }
                }
            }
        }
        
        // Slightly hacky fix to prevent inverted button settings on startup
        setParameter(isActiveBand1, getParameter(isActiveBand1));
        setParameter(isActiveBand2, getParameter(isActiveBand2));
        setParameter(isActiveBand3, getParameter(isActiveBand3));
        
        UIUpdateFlag = true;
    }
}


String MonstrAudioProcessor::floatVectorToString(const std::vector<float>& fData) const {
    String result {""};
    
    if (fData.size() < 1) {
        return result;
    }
    
    for (int iii {0}; iii < (fData.size() - 1); iii++) {
        result << String(fData[iii])<<",";
    }
    
    result << String(fData[fData.size() - 1]);
    
    return result;
}

int MonstrAudioProcessor::stringToFloatVector(const String sFloatCSV, std::vector<float>& fData, int maxNumFloat) const {
    StringArray tokenizer;
    int tokenCount {tokenizer.addTokens(sFloatCSV, ",","")};
    int resultCount {(maxNumFloat <= tokenCount) ? maxNumFloat : tokenCount};
    
    for (int iii {0}; iii < resultCount; iii++) {
        fData.push_back(tokenizer[iii].getFloatValue());
    }
    
    return ((tokenCount <= maxNumFloat) ? resultCount : -1);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MonstrAudioProcessor();
}