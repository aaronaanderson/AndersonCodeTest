#include "Envelope.hpp"


Envelope::Envelope()
{
    envelopeTree = juce::ValueTree(envelopeID);
}

void Envelope::addPoint(double time, double value)
{
    auto pointBranch = juce::ValueTree(pointID);
    pointBranch.setProperty(timeID, time, nullptr);
    pointBranch.setProperty(valueID, value, nullptr);
    envelopeTree.addChild(pointBranch, indexForTimeValue(time), nullptr);
}
void Envelope::deletePoint(int index)
{
    envelopeTree.removeChild(index, nullptr);
}
double Envelope::getValue(double time)
{
    if(getNumberPoints() < 1)
        return 0.5;
    
    int index = indexForTimeValue(time);
    if(index < 1)
        return envelopeTree.getChild(0)[valueID];
    if(index >= getNumberPoints())
        return envelopeTree.getChild(getNumberPoints()-1)[valueID];
    
    return interpolateLinear(envelopeTree.getChild(index-1)[timeID], envelopeTree.getChild(index-1)[valueID],
                             envelopeTree.getChild(index)[timeID], envelopeTree.getChild(index)[valueID], 
                             time);
}
int Envelope::getNumberPoints()
{
    return envelopeTree.getNumChildren();
}
int Envelope::indexForTimeValue(double time)
{
    jassert(time >= 0.0 && time <= 1.0);
    // Note this strategy assumes the tree is already sorted by point time
    for(int i = 0; i < getNumberPoints(); ++i)
    {
        //which index proceeds the new point
        if(static_cast<double>(envelopeTree.getChild(i)[timeID]) > time)
        {
            return i;
        }
    }
    //if nothing was found, then it will given the last valid index + 1
    return getNumberPoints();
}
double Envelope::interpolateLinear(double x1, double y1, double x2, double y2, double position)
{
    double scalar = (position - x1) / (x2 - x1);
    return (y1 * (1.0 - scalar)) + (y2 * scalar);
}