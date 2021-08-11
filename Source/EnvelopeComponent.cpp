#include "EnvelopeComponent.hpp"
#include "Envelope.hpp"

EnvelopeComponent::PointComponent::PointComponent(EnvelopeComponent& parent,juce::ValueTree branch)
  :  parentComponent(parent),
     pointBranch(branch)
{
    juce::Rectangle<int> r;
    r.setSize(15, 15);
    juce::Point<int> position = {static_cast<float>(branch[timeID]) * parentComponent.getWidth() , 
                                 static_cast<float>(branch[valueID]) * parentComponent.getHeight()};
    r.setCentre(position);
    setBounds(r);
}
void EnvelopeComponent::PointComponent::paint(juce::Graphics& graphics) 
{
    graphics.setColour(juce::Colour::fromRGB(75, 75, 75));
    graphics.fillEllipse(0, 0, getWidth(), getHeight());
}
void EnvelopeComponent::PointComponent::mouseDown(const juce::MouseEvent& mouseEvent)
{
    juce::ignoreUnused(mouseEvent);
    auto e = parentComponent.getEnvelopeRef();
    int index = parentComponent.getValueTree().indexOf(pointBranch);
    e.deletePoint(index);
}
//================================================================================
EnvelopeComponent::EnvelopeComponent(juce::Component& parent, Envelope& envelope)
  :  parentComponent(parent), 
     envelopeReference(envelope)
{
    envelopeReference.getValueTree().addListener(this);
    setVisible(true);
}
EnvelopeComponent::~EnvelopeComponent()
{
    envelopeReference.getValueTree().removeListener(this);
}
void EnvelopeComponent::mouseDown(const juce::MouseEvent& mouseEvent)
{
    envelopeReference.addPoint(mouseEvent.x * normalizationScalar.x, 
                               mouseEvent.y * normalizationScalar.y);
}

void EnvelopeComponent::mouseMove(const juce::MouseEvent& mouseEvent)
{   //used only to position
    lastXMousePosition = mouseEvent.getPosition().getX();
    repaint();
}
void EnvelopeComponent::paint(juce::Graphics& graphics)
{
    graphics.fillAll (juce::Colour::fromRGB(160, 160, 160));
    graphics.setColour(juce::Colour::fromRGB(0, 0, 0));
    juce::Point<float> previousPoint;
    if(envelopeReference.getNumberPoints() < 1)
    {
        graphics.drawLine(0.0f, getHeight() * 0.5f, getWidth(), getHeight() * 0.5f);
    }else
    {
        for(int i = 0; i < envelopeReference.getNumberPoints(); ++i)
        {
            auto pointBranch = envelopeReference.getValueTree().getChild(i);
            juce::Point<float> p = {static_cast<float>(pointBranch[timeID]) * getWidth(), 
                                    static_cast<float>(pointBranch[valueID]) * getHeight()};
            if(i > 0)
            {
                graphics.drawLine(previousPoint.getX(), previousPoint.getY(), p.getX(), p.getY());
            }
            previousPoint = p;
        }
        //draw edge-case lines
        auto pointBranch = envelopeReference.getValueTree().getChild(0);
        juce::Point<float> p = {static_cast<float>(pointBranch[timeID]) * getWidth(), 
                                static_cast<float>(pointBranch[valueID]) * getHeight()};
        
        graphics.drawLine(0.0f, p.getY(), p.getX(), p.getY());

        int lastChildIndex = envelopeReference.getValueTree().getNumChildren() - 1;
        pointBranch = envelopeReference.getValueTree().getChild(lastChildIndex);
        p = {static_cast<float>(pointBranch[timeID]) * getWidth(), 
             static_cast<float>(pointBranch[valueID]) * getHeight()};
        graphics.drawLine(p.getX(), p.getY(), getWidth(), p.getY());
    }    
    //Small rec circle to show .getValue() accuracy
    juce::Rectangle<float> r;
    r.setCentre(lastXMousePosition - 5, 
                envelopeReference.getValue(lastXMousePosition * normalizationScalar.getX()) * getHeight() - 5);
    r.setSize(10, 10);
    graphics.setColour(juce::Colours::red);
    graphics.fillEllipse(r);
}
void EnvelopeComponent::resized()
{
    normalizationScalar.x = 1.0 / static_cast<double>(getWidth());
    normalizationScalar.y = 1.0 / static_cast<double>(getHeight());
    layoutPointComponents();
}   

void EnvelopeComponent::removePointComponent(EnvelopeComponent::PointComponent* p)
{
    int i = pointComponents.indexOf(p);
    pointComponents.remove(i);
    parentComponent.removeChildComponent(p);
}
juce::ValueTree EnvelopeComponent::getValueTree()
{
    return envelopeReference.getValueTree();
}
void EnvelopeComponent::valueTreeChildAdded(juce::ValueTree& parentTree,
                                            juce::ValueTree& newChildTree)
{
    juce::ignoreUnused(parentTree);
    auto c = pointComponents.add(new PointComponent(*this, newChildTree));
    addAndMakeVisible(c);
    repaint();
}
void EnvelopeComponent::valueTreeChildRemoved (juce::ValueTree& parentTree,
                                               juce::ValueTree& childWhichHasBeenRemoved,
                                               int indexFromWhichChildWasRemoved)
{
    juce::ignoreUnused(parentTree);juce::ignoreUnused(indexFromWhichChildWasRemoved);
    auto c = getComponentForValueTree(childWhichHasBeenRemoved);
    removePointComponent(c);//remove self from parent list
    repaint();
}                                            
EnvelopeComponent::PointComponent* EnvelopeComponent::getComponentForValueTree(const juce::ValueTree& tree)
{
    for(auto c : pointComponents)
        if(c->getPointBranch() == tree)
            return c;

    return nullptr;
}
void EnvelopeComponent::layoutPointComponents()
{
    for(auto c : pointComponents)
    {
        juce::Rectangle<int> r;
        r.setSize(15, 15);
        auto pointBranch = c->getPointBranch();
        r.setCentre(static_cast<float>(pointBranch[timeID]) * parentComponent.getWidth(), 
                    static_cast<float>(pointBranch[valueID]) * parentComponent.getHeight());
        c->setBounds(r);
    }
}