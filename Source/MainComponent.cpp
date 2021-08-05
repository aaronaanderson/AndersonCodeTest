#include "MainComponent.hpp"

MainComponent::MainComponent()
  :  envelopeComponent(*this, envelope)
{
    setSize (600, 400);
    addAndMakeVisible(envelopeComponent);
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
//    envelopeComponent.centreWithSize(getWidth() - 20, getHeight() - 20);
   envelopeComponent.setBounds(getBounds());
}
