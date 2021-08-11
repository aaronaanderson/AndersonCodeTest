#ifndef __EnvelopeComponent_hpp__
#define __EnvelopeComponent_hpp__

#include <juce_gui_extra/juce_gui_extra.h>

class Envelope;
class EnvelopeComponent : public juce::Component, 
                          private juce::ValueTree::Listener
{
    public:
    EnvelopeComponent(juce::Component& parent, Envelope& envelope);
    ~EnvelopeComponent();

    void paint(juce::Graphics&) override;
    void resized() override;
    juce::ValueTree getValueTree();
    Envelope& getEnvelopeRef(){return envelopeReference;}
    private:
    juce::Component& parentComponent;
    Envelope& envelopeReference;
    juce::Point<double> normalizationScalar;

    class PointComponent : public juce::Component
    {
        public:
        PointComponent(EnvelopeComponent& parent, juce::ValueTree branch, juce::Point<int> position);
        void paint(juce::Graphics&) override;
        juce::ValueTree getPointBranch(){return pointBranch;}

        private:
        void mouseDown(const juce::MouseEvent&) override;
        EnvelopeComponent& parentComponent;
        juce::ValueTree pointBranch;
    };
    void removePointComponent(PointComponent*);

    private:
    juce::OwnedArray<PointComponent> pointComponentPtrs;

    void mouseDown(const juce::MouseEvent&) override;
    void mouseMove(const juce::MouseEvent&) override;

    void valueTreeChildAdded (juce::ValueTree& parentTree,
                              juce::ValueTree& childWhichHasBeenAdded) override;
    void valueTreeChildRemoved (juce::ValueTree& parentTree,
                                juce::ValueTree& childWhichHasBeenRemoved,
                                int indexFromWhichChildWasRemoved) override;      
    PointComponent* getComponentForValueTree(const juce::ValueTree&);    
    void layoutPointComponents();      
    int lastXMousePosition;              
};

#endif