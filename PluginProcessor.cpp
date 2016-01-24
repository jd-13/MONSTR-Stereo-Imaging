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
    mMONSTR.band1.makeBandBottom(true);
    mMONSTR.band1.makeBandTop(false);
    mMONSTR.band1.setLowCutoff(20);
    mMONSTR.band1.setHighCutoff(CROSSOVERLOWER_DEFAULT);
    mMONSTR.band1.setWidth(WIDTH_DEFAULT);
    mMONSTR.band1.setIsbypassed(BANDSWITCH_DEFAULT);
    
    mMONSTR.band2.makeBandBottom(false);
    mMONSTR.band2.makeBandTop(false);
    mMONSTR.band2.setLowCutoff(CROSSOVERLOWER_DEFAULT);
    mMONSTR.band2.setHighCutoff(CROSSOVERUPPER_DEFAULT);
    mMONSTR.band2.setWidth(WIDTH_DEFAULT);
    mMONSTR.band2.setIsbypassed(BANDSWITCH_DEFAULT);
    
    mMONSTR.band3.makeBandBottom(false);
    mMONSTR.band3.makeBandTop(false);
    mMONSTR.band3.setLowCutoff(CROSSOVERUPPER_DEFAULT);
    mMONSTR.band3.setHighCutoff(20000);
    mMONSTR.band3.setWidth(WIDTH_DEFAULT);
    mMONSTR.band3.setIsbypassed(BANDSWITCH_DEFAULT);
    
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
        case isBypassedBand1:
            return mMONSTR.band1.getIsBypassed();
            
        case widthBand1:
            return TranslateParam_Inter2Norm(mMONSTR.band1.getWidth(), WIDTH_MIN, WIDTH_MAX);
            
        
        
        case crossoverLower:
            return TranslateParam_Inter2Norm(mMONSTR.band1.getHighCutoff(), CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX);
            
        
        
        case isBypassedBand2:
            return mMONSTR.band2.getIsBypassed();
            
        case widthBand2:
            return mMONSTR.band2.getWidth();
            
        
        
        case crossoverUpper:
            return TranslateParam_Inter2Norm(mMONSTR.band2.getHighCutoff(), CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX);
            
        
        
        case isBypassedBand3:
            return mMONSTR.band3.getIsBypassed();
            
        case widthBand3:
            return TranslateParam_Inter2Norm(mMONSTR.band3.getWidth(), WIDTH_MIN, WIDTH_MAX);
            
        
        
        default:
            return 0.0f;
    }
}

void MonstrAudioProcessor::setParameter (int index, float newValue)
{
    switch (index) {
        case isBypassedBand1:
            mMONSTR.band1.setIsbypassed(newValue < 0.5);
            break;
            
        case widthBand1:
            mMONSTR.band1.setWidth(TranslateParam_Norm2Inter(newValue, WIDTH_MIN, WIDTH_MAX));
            break;
            
            
            
        case crossoverLower:
            mMONSTR.band1.setHighCutoff(TranslateParam_Norm2Inter(newValue, CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX));
            mMONSTR.band2.setLowCutoff(TranslateParam_Norm2Inter(newValue, CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX));
            break;
            
            
            
        case isBypassedBand2:
            mMONSTR.band2.setIsbypassed(newValue < 0.5);
            break;
            
        case widthBand2:
            mMONSTR.band2.setWidth(TranslateParam_Norm2Inter(newValue, WIDTH_MIN, WIDTH_MAX));
            break;
            
            
            
        case crossoverUpper:
            mMONSTR.band2.setHighCutoff(TranslateParam_Norm2Inter(newValue, CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX));
            mMONSTR.band3.setLowCutoff(TranslateParam_Norm2Inter(newValue, CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX));
            break;
            
            
            
        case isBypassedBand3:
            mMONSTR.band3.setIsbypassed(newValue < 0.5);
            break;
            
        case widthBand3:
            mMONSTR.band3.setWidth(TranslateParam_Norm2Inter(newValue, WIDTH_MIN, WIDTH_MAX));
            
        default:
            break;
    }
}

const String MonstrAudioProcessor::getParameterName (int index)
{
    switch (index) {
        case isBypassedBand1:
            return SWITCHBAND1_STR;
            
        case widthBand1:
            return WIDTHBAND1_STR;
            
            
            
        case crossoverLower:
            return CROSSOVERLOWER_STR;
            
            
            
        case isBypassedBand2:
            return SWITCHBAND2_STR;
            
        case widthBand2:
            return WIDTHBAND2_STR;
            
            
            
        case crossoverUpper:
            return CROSSOVERUPPER_STR;
            
            
            
        case isBypassedBand3:
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
        case isBypassedBand1:
            return String(mMONSTR.band1.getIsBypassed());
            
        case widthBand1:
            return String(TranslateParam_Inter2Norm(mMONSTR.band1.getWidth(), WIDTH_MIN, WIDTH_MAX));
            
            
            
        case crossoverLower:
            return String(TranslateParam_Inter2Norm(mMONSTR.band1.getHighCutoff(), CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX));
            
            
            
        case isBypassedBand2:
            return String(mMONSTR.band2.getIsBypassed());
            
        case widthBand2:
            return String(TranslateParam_Inter2Norm(mMONSTR.band2.getWidth(), WIDTH_MIN, WIDTH_MAX));
            
            
            
        case crossoverUpper:
            return String(TranslateParam_Inter2Norm(mMONSTR.band2.getHighCutoff(), CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX));
            
            
            
        case isBypassedBand3:
            return String(mMONSTR.band3.getIsBypassed());
            
        case widthBand3:
            return String(TranslateParam_Inter2Norm(mMONSTR.band3.getWidth(), WIDTH_MIN, WIDTH_MAX));
            
        default:
            return String::empty;
    }
}

bool MonstrAudioProcessor::isParameterAutomatable(int parameterIndex) const {
    switch (parameterIndex) {
        case isBypassedBand1:
        case isBypassedBand2:
        case isBypassedBand3:
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
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* inLeftSample = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
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
        setParameter(isBypassedBand1, getParameter(isBypassedBand1));
        setParameter(isBypassedBand2, getParameter(isBypassedBand2));
        setParameter(isBypassedBand3, getParameter(isBypassedBand3));
        
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
