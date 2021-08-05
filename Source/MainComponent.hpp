#ifndef __MainComponent_hpp__
#define __MainComponent_hpp__

#include <juce_gui_extra/juce_gui_extra.h>
#include "Envelope.hpp"
#include "EnvelopeComponent.hpp"

class MainComponent   : public juce::Component
{
public:
    MainComponent();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Envelope envelope;
    EnvelopeComponent envelopeComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
#endif 