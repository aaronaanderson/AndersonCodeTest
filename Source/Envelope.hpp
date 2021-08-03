#ifndef __Envelope_hpp__
#define __Envelope_hpp__

#include <juce_gui_extra/juce_gui_extra.h>


class Envelope 
{
    public:
    Envelope();

    void addPoint(double time, double value);
    void deletePoint(int index);
    double getValue(double time);
    int getNumberPoints();
        
    private:
    juce::ValueTree envelopeTree;

};

#endif