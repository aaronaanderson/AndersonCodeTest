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

    return 0.0;
}
int Envelope::getNumberPoints()
{
    return envelopeTree.getNumChildren();
}
int Envelope::indexForTimeValue(double time)
{
    jassert(time >= 0.0 && time <= 1.0);
    // Note this assumes the tree is already sorted by point time
    for(int i = 0; i < getNumberPoints(); ++i)
    {
        //which index proceeds the new point
        if(static_cast<double>(envelopeTree.getChild(i)[timeID]) > time)
        {
            return i;
        }
    }
    //if nothing was found, then it will given the last index
    return getNumberPoints();
}