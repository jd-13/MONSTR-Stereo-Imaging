/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.9

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "UIUtils.h"
//[/MiscUserDefs]

//==============================================================================
MonstrAudioProcessorEditor::MonstrAudioProcessorEditor (MonstrAudioProcessor& ownerFilter)
    : CoreProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    crossoverWrapper.reset (new MONSTRCrossoverWrapperComponent (getProcessor()));
    addAndMakeVisible (crossoverWrapper.get());
    crossoverWrapper->setName ("Crossover View");

    crossoverWrapper->setBounds (16, 40, 608, 210);

    AddBandBtn.reset (new juce::TextButton ("Add Band Button"));
    addAndMakeVisible (AddBandBtn.get());
    AddBandBtn->setTooltip (TRANS ("Adds a new band"));
    AddBandBtn->setButtonText (TRANS ("Add Band"));
    AddBandBtn->addListener (this);

    AddBandBtn->setBounds (365, 256, 275, 34);

    RemoveBandBtn.reset (new juce::TextButton ("Remove Band Button"));
    addAndMakeVisible (RemoveBandBtn.get());
    RemoveBandBtn->setTooltip (TRANS ("Removes the highest band"));
    RemoveBandBtn->setButtonText (TRANS ("Remove Band"));
    RemoveBandBtn->addListener (this);

    RemoveBandBtn->setBounds (0, 256, 275, 34);

    widthValueLbl.reset (new MONSTRWidthLabel ("Width Value Label",
                                               juce::String()));
    addAndMakeVisible (widthValueLbl.get());
    widthValueLbl->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    widthValueLbl->setJustificationType (juce::Justification::centred);
    widthValueLbl->setEditable (false, false, false);
    widthValueLbl->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    widthValueLbl->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    widthValueLbl->setBounds (288, 261, 64, 24);

    tooltipLbl.reset (new juce::Label ("Tooltip Label",
                                       juce::String()));
    addAndMakeVisible (tooltipLbl.get());
    tooltipLbl->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    tooltipLbl->setJustificationType (juce::Justification::centred);
    tooltipLbl->setEditable (false, false, false);
    tooltipLbl->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    tooltipLbl->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    tooltipLbl->setBounds (8, 294, 624, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (640, 318);


    //[Constructor] You can add your own custom stuff here..
    startTimer(40);

    _assignLookAndFeelToAllChildren(customLookAndFeel);

    // This is needed for the fonts to be applied
    MONSTRLookAndFeel::setDefaultLookAndFeel(&customLookAndFeel);

    // Start tooltip label
    addMouseListener(&_tooltipLabelUpdater, true);
    _tooltipLabelUpdater.start(tooltipLbl.get(), getAudioProcessor()->wrapperType);
    tooltipLbl->setColour(Label::textColourId, UIUtils::lightGrey);

    AddBandBtn->setColour(TextButton::textColourOnId, UIUtils::mainHighlight);
    RemoveBandBtn->setColour(TextButton::textColourOnId, UIUtils::mainHighlight);

    AddBandBtn->setColour(TextButton::textColourOffId, UIUtils::lightGrey);
    RemoveBandBtn->setColour(TextButton::textColourOffId, UIUtils::lightGrey);

    widthValueLbl->setColour(Label::textColourId, UIUtils::mainHighlight);
    crossoverWrapper->start(widthValueLbl.get(), tooltipLbl.get());

    // Call this manually once to make sure the UI reflects the parameters' states correctly
    _onParameterUpdate();
    //[/Constructor]
}

MonstrAudioProcessorEditor::~MonstrAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    crossoverWrapper->stop();
    widthValueLbl->stop();
    _tooltipLabelUpdater.stop();
    //[/Destructor_pre]

    crossoverWrapper = nullptr;
    AddBandBtn = nullptr;
    RemoveBandBtn = nullptr;
    widthValueLbl = nullptr;
    tooltipLbl = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    _removeLookAndFeelFromAllChildren();
    //[/Destructor]
}

//==============================================================================
void MonstrAudioProcessorEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    //[UserPaint] Add your own custom painting code here..

    Image bg {ImageCache::getFromMemory(BinaryData::MONSTR_Background_png, BinaryData::MONSTR_Background_pngSize)};
    g.drawImage(bg, 0, 0, 640, 318, 0, 0, 2 * 640, 2 * 318);

    //[/UserPaint]
}

void MonstrAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MonstrAudioProcessorEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    MonstrAudioProcessor* ourProcessor {getProcessor()};
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == AddBandBtn.get())
    {
        //[UserButtonCode_AddBandBtn] -- add your button handler code here..
        ourProcessor->addBand();
        //[/UserButtonCode_AddBandBtn]
    }
    else if (buttonThatWasClicked == RemoveBandBtn.get())
    {
        //[UserButtonCode_RemoveBandBtn] -- add your button handler code here..
        ourProcessor->removeBand();
        //[/UserButtonCode_RemoveBandBtn]
    }

    //[UserbuttonClicked_Post]
    crossoverWrapper->onParameterUpdate();
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MonstrAudioProcessorEditor::timerCallback() {
    widthValueLbl->refreshValue();
    crossoverWrapper->onImagerUpdate();
}

void MonstrAudioProcessorEditor::_onParameterUpdate() {
    crossoverWrapper->onParameterUpdate();

    MonstrAudioProcessor* ourProcessor {getProcessor()};

    // Disable the buttons when at the minimum/maximum number of bands

    if (ourProcessor->numBands->get() == WECore::MONSTR::Parameters::NUM_BANDS.minValue) {
        AddBandBtn->setEnabled(true);
        RemoveBandBtn->setEnabled(false);
    } else if (ourProcessor->numBands->get() == WECore::MONSTR::Parameters::NUM_BANDS.maxValue) {
        AddBandBtn->setEnabled(false);
        RemoveBandBtn->setEnabled(true);
    } else {
        AddBandBtn->setEnabled(true);
        RemoveBandBtn->setEnabled(true);
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MonstrAudioProcessorEditor"
                 componentName="" parentClasses="public WECore::JUCEPlugin::CoreProcessorEditor, public Timer"
                 constructorParams="MonstrAudioProcessor&amp; ownerFilter" variableInitialisers="CoreProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="640" initialHeight="318">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="Crossover View" id="e7b7ed6ee8457913" memberName="crossoverWrapper"
                    virtualName="MONSTRCrossoverWrapperComponent" explicitFocusOrder="0"
                    pos="16 40 608 210" class="juce::Component" params="getProcessor()"/>
  <TEXTBUTTON name="Add Band Button" id="9e80e2964e937f97" memberName="AddBandBtn"
              virtualName="" explicitFocusOrder="0" pos="365 256 275 34" tooltip="Adds a new band"
              buttonText="Add Band" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Remove Band Button" id="2ef4417e3e0b973d" memberName="RemoveBandBtn"
              virtualName="" explicitFocusOrder="0" pos="0 256 275 34" tooltip="Removes the highest band"
              buttonText="Remove Band" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="Width Value Label" id="b0626778082c566d" memberName="widthValueLbl"
         virtualName="MONSTRWidthLabel" explicitFocusOrder="0" pos="288 261 64 24"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="Tooltip Label" id="a4a550f0da714be5" memberName="tooltipLbl"
         virtualName="" explicitFocusOrder="0" pos="8 294 624 24" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

