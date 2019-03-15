/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ff_meters/ff_meters.h"


//==============================================================================
VolumeSliderNewAudioProcessor::VolumeSliderNewAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
	treeState(*this, nullptr, "PARAMETER", createParameterLayout())
#endif
{
}

//==============================================================================

VolumeSliderNewAudioProcessor::~VolumeSliderNewAudioProcessor()
{

}
//==============================================================================

AudioProcessorValueTreeState::ParameterLayout VolumeSliderNewAudioProcessor::createParameterLayout()
{
	std::vector <std::unique_ptr<RangedAudioParameter>> params;

	auto gainParam = std::make_unique<AudioParameterFloat>(GAIN_ID, GAIN_NAME, -48.0f, 0.0f, 0.0f);
	auto polarityParam = std::make_unique<AudioParameterBool>(POLARITY_ID, POLARITY_NAME, true);
	auto highPassParam = std::make_unique<AudioParameterFloat>(HPF_ID, HPF_NAME, 0.0f, 500.0f, 0.0f);
	auto saturationParam = std::make_unique<AudioParameterFloat>(SAT_ID, SAT_NAME, 0.0f, 100.0f, 0.0f);
	auto comboBoxParam = std::make_unique<AudioParameterChoice>(CMB_ID, CMB_NAME, StringArray("Hard Clipper", "Soft Clipper","Smooth"), 0);


	params.push_back(std::move(gainParam));
	params.push_back(std::move(polarityParam));
	params.push_back(std::move(highPassParam));
	params.push_back(std::move(saturationParam));
	params.push_back(std::move(comboBoxParam));

	return { params.begin(), params.end() };

}


//==============================================================================
const String VolumeSliderNewAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool VolumeSliderNewAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool VolumeSliderNewAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool VolumeSliderNewAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double VolumeSliderNewAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int VolumeSliderNewAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int VolumeSliderNewAudioProcessor::getCurrentProgram()
{
	return 0;
}

void VolumeSliderNewAudioProcessor::setCurrentProgram(int index)
{
}

const String VolumeSliderNewAudioProcessor::getProgramName(int index)
{
	return {};
}

void VolumeSliderNewAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void VolumeSliderNewAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{

	lastSampleRate = sampleRate;

	dsp::ProcessSpec hpf;
	hpf.sampleRate = sampleRate;
	hpf.maximumBlockSize = samplesPerBlock;
	hpf.numChannels = getTotalNumOutputChannels();

	highpassFilter.prepare(hpf);
	highpassFilter.reset();
	updateFilter();

	//Meter
	outline.setSize(getTotalNumInputChannels(), 1024);

}
//==============================================================================

void VolumeSliderNewAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}
//==============================================================================

#ifndef JucePlugin_PreferredChannelConfigurations
bool VolumeSliderNewAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

//==============================================================================

void VolumeSliderNewAudioProcessor::updateFilter()
{
	auto freq = *treeState.getRawParameterValue(HPF_ID);

	*highpassFilter.state = *dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(lastSampleRate, freq);


}
//==============================================================================

void VolumeSliderNewAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

	const int totalNumInputChannels = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();



	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());


	//============================ Drives ===================================

	for (int samples = 0; samples < totalNumInputChannels; ++samples)
	{

		auto driveMenu = treeState.getRawParameterValue(CMB_ID);

		//HardClip
		if (*driveMenu == 0)
		{
			auto channelDrive1 = buffer.getWritePointer(samples);
			auto saturation1Value = treeState.getRawParameterValue(SAT_ID);
			if (*saturation1Value == 0)
			{
				channelDrive1[samples] = channelDrive1[samples];
			}
			else
			{
				for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
				{
					float inputSample = channelDrive1[sample];
					float inputSample1 = 1.5 * inputSample - 0.5 * pow(inputSample, 3);
					channelDrive1[sample] = jlimit(-1.0f, 1.0f, Decibels::decibelsToGain(*saturation1Value)*inputSample1);
				}
			}
		}
		//SoftClip
		else if (*driveMenu == 1)
		{
			auto channelDrive2 = buffer.getWritePointer(samples);
			auto saturation2Value = treeState.getRawParameterValue(SAT_ID);
			if (*saturation2Value == 0)
			{
				channelDrive2[samples] = channelDrive2[samples];
			}
			else
			{
				for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
				{
					float inputSample2 = channelDrive2[sample];
					channelDrive2[sample] = jlimit(-1.0f, 1.0f, Decibels::decibelsToGain(*saturation2Value) * (inputSample2));
				}
			}
		}
		//Smooth
		else if (*driveMenu == 2)
		{
			auto channelDrive3 = buffer.getWritePointer(samples);
			auto saturation3Value = treeState.getRawParameterValue(SAT_ID);
			if (*saturation3Value == 0)
			{
				channelDrive3[samples] = channelDrive3[samples];
			}
			else
			{
				for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
				{
					float inputSample3 = channelDrive3[sample];
					channelDrive3[sample] = 2 / 3.14159265 * atan(inputSample3*(*saturation3Value));
				}
			}
		}
	}

	//HPF 
	dsp::AudioBlock<float> block(buffer);
	updateFilter();
	highpassFilter.process(dsp::ProcessContextReplacing<float>(block));

	//Volume
	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto channelData = buffer.getWritePointer(channel);
		auto sliderGainValue = treeState.getRawParameterValue(GAIN_ID);
		auto toggleButtonValue = treeState.getRawParameterValue(POLARITY_ID);
		auto highPassFilterValue = treeState.getRawParameterValue(HPF_ID);

		for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			channelData[sample] = buffer.getSample(channel, sample) * Decibels::decibelsToGain(*sliderGainValue);

			//Polarity
			if (*toggleButtonValue == true)
			{
				channelData[sample] = channelData[sample];
			}
			else
				channelData[sample] *= -1;
		}
	}

	//Peak Meters
	meterSource.measureBlock(buffer);
	outline.pushBlock(buffer, buffer.getNumSamples());

}
//==============================================================================
bool VolumeSliderNewAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}
//==============================================================================

AudioProcessorEditor* VolumeSliderNewAudioProcessor::createEditor()
{
	return new VolumeSliderNewAudioProcessorEditor(*this);
}
//==============================================================================
void VolumeSliderNewAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.

	auto state = treeState.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);

}

void VolumeSliderNewAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(treeState.state.getType()))
			treeState.replaceState(ValueTree::fromXml(*xmlState));


}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new VolumeSliderNewAudioProcessor();
}


//==============================================================================
