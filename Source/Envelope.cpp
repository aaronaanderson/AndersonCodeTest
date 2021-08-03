#include "Envelope.hpp"

static const juce::Identifier envelopeID("envelope");
static const juce::Identifier pointID("point");
static const juce::Identifier timeID("time");
static const juce::Identifier valueID("value");

Envelope::Envelope()
{
    envelopeTree = juce::ValueTree(envelopeID);
}

void Envelope::addPoint(double time, double value)
{
    auto pointBranch = juce::ValueTree(pointID);
    pointBranch.setProperty(timeID, time, nullptr);
    pointBranch.setProperty(valueID, value, nullptr);
}
void Envelope::deletePoint(int index)
{
    //todo ensure sorted
    envelopeTree.removeChild(index, nullptr);
}
double Envelope::getValue(double time)
{
    return 0.0;
}
int Envelope::getNumberPoints()
{
    return envelopeTree.getNumChildren();
}