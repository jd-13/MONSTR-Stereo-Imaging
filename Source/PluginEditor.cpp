/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MonstrAudioProcessorEditor::MonstrAudioProcessorEditor (MonstrAudioProcessor& ownerFilter)
    : CoreProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    crossoverView.reset (new MONSTRCrossoverComponent (getProcessor()));
    addAndMakeVisible (crossoverView.get());
    crossoverView->setName ("Crossover View");

    crossoverView->setBounds (40, 40, 560, 210);

    AddBandBtn.reset (new juce::TextButton ("Add Band Button"));
    addAndMakeVisible (AddBandBtn.get());
    AddBandBtn->setButtonText (TRANS("+"));
    AddBandBtn->addListener (this);

    AddBandBtn->setBounds (336, 256, 40, 24);

    RemoveBandBtn.reset (new juce::TextButton ("Remove Band Button"));
    addAndMakeVisible (RemoveBandBtn.get());
    RemoveBandBtn->setButtonText (TRANS("-"));
    RemoveBandBtn->addListener (this);

    RemoveBandBtn->setBounds (256, 256, 40, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (640, 290);


    //[Constructor] You can add your own custom stuff here..
    _assignLookAndFeelToAllChildren(customLookAndFeel);

    // Call this manually once to make sure the UI reflects the parameters' states correctly
    _onParameterUpdate();
    //[/Constructor]
}

MonstrAudioProcessorEditor::~MonstrAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    crossoverView = nullptr;
    AddBandBtn = nullptr;
    RemoveBandBtn = nullptr;


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
    g.drawImage(bg, 0, 0, 640, 290, 0, 0, 5 * 640, 5 * 290);

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
    crossoverView->updateParameters();
    crossoverView->repaint();
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MonstrAudioProcessorEditor::_onParameterUpdate() {
    crossoverView->updateParameters();
    crossoverView->repaint();

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
                 componentName="" parentClasses="public WECore::JUCEPlugin::CoreProcessorEditor"
                 constructorParams="MonstrAudioProcessor&amp; ownerFilter" variableInitialisers="CoreProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="640" initialHeight="290">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="Crossover View" id="e7b7ed6ee8457913" memberName="crossoverView"
                    virtualName="MONSTRCrossoverComponent" explicitFocusOrder="0"
                    pos="40 40 560 210" class="juce::Component" params="getProcessor()"/>
  <TEXTBUTTON name="Add Band Button" id="9e80e2964e937f97" memberName="AddBandBtn"
              virtualName="" explicitFocusOrder="0" pos="336 256 40 24" buttonText="+"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Remove Band Button" id="2ef4417e3e0b973d" memberName="RemoveBandBtn"
              virtualName="" explicitFocusOrder="0" pos="256 256 40 24" buttonText="-"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

