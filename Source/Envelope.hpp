#ifndef __Envelope_hpp__
#define __Envelope_hpp__

#include <juce_gui_extra/juce_gui_extra.h>

static const juce::Identifier envelopeID("envelope");
static const juce::Identifier pointID("point");
static const juce::Identifier timeID("time");
static const juce::Identifier valueID("value");

class Envelope 
{
    public:
    Envelope();

    void addPoint(double time, double value);
    void deletePoint(int index);
    double getValue(double time);
    int getNumberPoints();
    juce::ValueTree& getValueTree(){return envelopeTree;}
        
    private:
    juce::ValueTree envelopeTree;
    int indexForTimeValue(double time);//returns insertion index for given time
    double interpolateLinear(double x1, double y1, double x2, double y2, double pos);
};

#endif