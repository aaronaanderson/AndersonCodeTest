#ifndef __EnvelopeComponent_hpp__
#define __EnvelopeComponent_hpp__

#include <juce_gui_extra/juce_gui_extra.h>

class Envelope;
class EnvelopeComponent : public juce::Component, 
                          private juce::MouseListener
{
    public:
    EnvelopeComponent(juce::Component& parent, Envelope& envelope);

    private:
    juce::Component& parentComponent;
    Envelope& envelopeReference;
    void mouseDown(const juce::MouseEvent&) override;
    void mouseDrag(const juce::MouseEvent&) override;
};

#endif