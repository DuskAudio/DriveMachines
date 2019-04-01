/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include "ff_meters/ff_meters.h"

//==============================================================================
VolumeSliderNewAudioProcessorEditor::VolumeSliderNewAudioProcessorEditor(VolumeSliderNewAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	//Allocating on the Heap
	volumeValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, volumeSlider);
	invertValue = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(processor.treeState, POLARITY_ID, invertToggle);
	highPassValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, HPF_ID, highPassSlider);
	saturationValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, SAT_ID, saturationSlider);
	drivesMenuValue = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.treeState, CMB_ID, drivesMenu);

	//Background
	background = ImageCache::getFromMemory(BinaryData::bg_duskSatur_png, BinaryData::bg_duskSatur_pngSize);

	//Volume Label
	volumeLabel.setText("Volume", dontSendNotification);
	//volumeLabel.setColour(Label::outlineColourId, Colours::orange);
	volumeLabel.setJustificationType(juce::Justification::horizontallyCentred);
	volumeLabel.attachToComponent(&volumeSlider, false);

	addAndMakeVisible(&volumeLabel);

	//Volume Slider
	volumeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	volumeSlider.setColour(Slider::thumbColourId, Colours::orange);
	volumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
	volumeSlider.setTextValueSuffix(" dB");

	addAndMakeVisible(&volumeSlider);

	//==============================================================

	//HighPass Label
	highpassLabel.setText("HPF", dontSendNotification);
	highpassLabel.setJustificationType(juce::Justification::horizontallyCentred);
	//highpassLabel.setColour(Label::outlineColourId, Colours::orange);
	highpassLabel.attachToComponent(&highPassSlider, false);

	addAndMakeVisible(&highpassLabel);
	//HighPass Slider
	highPassSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	highPassSlider.setColour(Slider::thumbColourId, Colours::orange);
	highPassSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
	highPassSlider.setTextValueSuffix(" Hz");

	addAndMakeVisible(&highPassSlider);

	//==============================================================

	//Clipper Label
	saturationLabel.setText("Drive", dontSendNotification);
	//saturationLabel.setColour(Label::outlineColourId, Colours::mediumpurple);
	saturationLabel.setJustificationType(juce::Justification::horizontallyCentred);
	saturationLabel.attachToComponent(&saturationSlider, false);

	addAndMakeVisible(&saturationLabel);
	//Clipper Slider
	saturationSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	saturationSlider.setColour(Slider::thumbColourId, Colours::mediumpurple);
	saturationSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
	saturationSlider.setTextValueSuffix(" %");

	addAndMakeVisible(&saturationSlider);

	//==============================================================

	//Polarity reverse toggle Button
	invertToggle.setButtonText("Polarity");
	addAndMakeVisible(&invertToggle);


	//ComboBox Drives
	drivesMenu.addItem("Hard Clipper", 1);
	drivesMenu.addItem("Soft Clipper", 2);
	drivesMenu.addItem("Smoother"	 , 3);

	drivesMenu.setJustificationType(juce::Justification::centred);
	drivesMenu.setColour(ComboBox::backgroundColourId, Colours::transparentBlack);
	drivesMenu.setColour(ComboBox::outlineColourId, Colours::transparentBlack);
	drivesMenu.setColour(ComboBox::textColourId, Colours::orange);
	drivesMenu.setColour(ComboBox::buttonColourId, Colours::orange);
	addAndMakeVisible(&drivesMenu);



	//ff_audio Meter - Daniel JUCE discord
	{
		lnf = new FFAU::LevelMeterLookAndFeel();
		// adjust the colours to how you like them
		lnf->setColour(FFAU::LevelMeter::lmMeterBackgroundColour, juce::Colours::transparentBlack);
		lnf->setColour(FFAU::LevelMeter::lmBackgroundColour, juce::Colours::transparentBlack);
		//lnf->setColour(FFAU::LevelMeter::lmOutlineColour, juce::Colours::orange);
		lnf->setColour(FFAU::LevelMeter::lmTicksColour, juce::Colours::white);
		lnf->setColour(FFAU::LevelMeter::lmTextColour, juce::Colours::orange);
		lnf->setColour(FFAU::LevelMeter::lmMeterGradientLowColour, juce::Colours::orange);

		meter = new FFAU::LevelMeter(FFAU::LevelMeter::Horizontal); // See FFAU::LevelMeter::MeterFlags for options
		meter->setLookAndFeel(lnf);
		meter->setMeterSource(processor.getMeterSource());

		addAndMakeVisible(meter);
	}

	setSize(600, 400);
	
}

VolumeSliderNewAudioProcessorEditor::~VolumeSliderNewAudioProcessorEditor()
{
}

//==============================================================================
void VolumeSliderNewAudioProcessorEditor::paint(Graphics& g)
{

	//Background Image
	g.drawImageAt(background, 0, 0);

	//Outer Rounded rectangle
	auto r = getLocalBounds();
	auto topRoundedSquare = r.removeFromTop(50).reduced(10);
	auto midRoundedSquare = r.removeFromTop(220).reduced(10);
	auto botRoundedSquare = r.removeFromTop(130).reduced(10);


	auto top = topRoundedSquare.toFloat();
	g.setColour(Colours::purple);
	g.drawRoundedRectangle(top, 5.0f, 2.0f);

	auto mid = midRoundedSquare.toFloat();
	g.setColour(Colours::orange);
	g.drawRoundedRectangle(mid, 5.0f, 2.0f);

	auto bot = botRoundedSquare.toFloat();
	g.setColour(Colours::purple);
	g.drawRoundedRectangle(bot, 5.0f, 2.0f);

}



void VolumeSliderNewAudioProcessorEditor::resized()
{
	// Total Area
	auto r = getLocalBounds();
	
	auto topRoundedSquare = r.removeFromTop(50).reduced(10);
	auto midRoundedSquare = r.removeFromTop(220).reduced(10);
	auto botRoundedSquare = r.removeFromTop(130).reduced(10);
	
	//Meter Area
	auto meterArea = botRoundedSquare.removeFromLeft(botRoundedSquare.getWidth());
	meter->setBounds(meterArea.reduced(10));
	//creating the Sliders on the Mid Rectangle

	auto volumeArea = midRoundedSquare.removeFromLeft(midRoundedSquare.getWidth()/3);
	volumeSlider.setBounds(volumeArea.reduced(30));

	auto saturationArea = midRoundedSquare.removeFromLeft(midRoundedSquare.getWidth() / 2);
	saturationSlider.setBounds(saturationArea.reduced(20));

	auto highpassArea = midRoundedSquare.removeFromLeft(midRoundedSquare.getWidth());
	highPassSlider.setBounds(highpassArea.reduced(30));

	//Top area - combo box and Polarity

	auto invertArea = topRoundedSquare.removeFromLeft(topRoundedSquare.getCentreX());
	invertToggle.setBounds(invertArea);

	auto comboBoxArea = topRoundedSquare.removeFromRight(topRoundedSquare.getCentreX());
	drivesMenu.setBounds(comboBoxArea);

	
	
}

