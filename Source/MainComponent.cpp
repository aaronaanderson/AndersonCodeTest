#include "MainComponent.hpp"

MainComponent::MainComponent()
  :  envelopeComponent(*this, envelope)
{
    setSize (600, 400);
    addAndMakeVisible(envelopeComponent);
}

void MainComponent::paint (juce::Graphics& g)
{}

void MainComponent::resized()
{
    envelopeComponent.setBounds(getBounds());
}
