#include "EnvelopeComponent.hpp"

EnvelopeComponent::EnvelopeComponent(juce::Component& parent, Envelope& envelope)
  :  parentComponent(parent), 
     envelopeReference(envelope)
{
    setVisible(true);
}

void EnvelopeComponent::mouseDown(const juce::MouseEvent&)
{

}
void EnvelopeComponent::mouseDrag(const juce::MouseEvent&)
{

}