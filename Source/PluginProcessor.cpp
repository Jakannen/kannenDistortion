/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

constexpr float pi = 3.14159265358979323846f;

//==============================================================================
KannenDistortionAudioProcessor::KannenDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), state(*this, nullptr, "PARAMETERS", {
                                std::make_unique<juce::AudioParameterFloat>("drive", "Drive", 0.f, 1.f, 1.0f),
                                std::make_unique<juce::AudioParameterFloat>("range", "Range", 0.f, 3000.f, 1.0f),
                                std::make_unique<juce::AudioParameterFloat>("blend", "Blend", 0.f, 1.f, 1.0f),
                                std::make_unique<juce::AudioParameterFloat>("volume", "Volume", 0.f, 3.f, 1.0f)
                           })
#endif
{
}

KannenDistortionAudioProcessor::~KannenDistortionAudioProcessor()
{
}

//==============================================================================
const juce::String KannenDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KannenDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KannenDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KannenDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KannenDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KannenDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KannenDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KannenDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KannenDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void KannenDistortionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KannenDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void KannenDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KannenDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void KannenDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Get parameter values
    const float drive = *state.getRawParameterValue("drive");
    const float range = *state.getRawParameterValue("range");
    const float blend = *state.getRawParameterValue("blend");
    const float volume = *state.getRawParameterValue("volume");

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            // Apply volume first
            float cleanSig = *channelData;

            *channelData *= drive * range; // Apply drive and range
            const float safeBlend = (blend != 0.f) ? blend : 0.001f; // Avoid division by zero
            *channelData = (((((2.f / pi) * atan(*channelData) * safeBlend)) + (cleanSig * (1.f / safeBlend))) / 2) * volume;

            ++channelData;
        }
    }
}

juce::AudioProcessorValueTreeState& KannenDistortionAudioProcessor::getState()
{
    return state;
}
//==============================================================================
bool KannenDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KannenDistortionAudioProcessor::createEditor()
{
    return new KannenDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void KannenDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream stream(destData, false);
    state.state.writeToStream(stream);
}

void KannenDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::ValueTree tree = juce::ValueTree::readFromData(data, sizeInBytes);

    if (tree.isValid()) {
        state.state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KannenDistortionAudioProcessor();
}
