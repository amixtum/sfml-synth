#ifndef SYNTHCONTROLLER_H
#define SYNTHCONTROLLER_H

#include <vector>
#include <Leap.h>

#include "PhaseModulationStream.h"
#include "SpacePartition.h"

struct IndexRange
{
    int lowerBound;
    int upperBound;
};

// very work in progress right now
class SynthController
{
public:
    void playNote(int halfStepsFromA4)
    {
        if (pmStream.getStatus() != sf::Sound::Status::Playing)
        {
            pmStream.play();
        }

        pmStream.setCarrierNote(halfStepsFromA4);
        pmStream.setModulationNote(halfStepsFromA4 - 6);
    }

    void playLeapPartitionNote(Leap::Frame &frame)
    {
        int index = leapPartition.getYIndexFromFrame(frame, true);
        int mIndex = leapPartition.getYIndexFromFrame(frame, false);
        if (index != -1)
        {
            playNote(notePartition[index]);
            currentNote = index;
        }
        if (mIndex != -1)
        {
            pmStream.setModulationIndex(modulationIndexPartition[mIndex]);
        }
    }

    // testing function
    void CreateTestPartitions()
    {
        // note partition
        int nNotes = 8;
        int division = leapPartition.getYSubintervals() / nNotes;

        int currentNote = -12;

        int scaleInterval = 0;

        float modIndexMin = 0.5f;
        float modIndexMax = 5.f;

        float deltaMod = (modIndexMax - modIndexMin) / (float)(leapPartition.getYSubintervals());



        for (int i = 0; i < leapPartition.getYSubintervals(); i++)
        {
            if (i % division == 0)
            {
                scaleInterval = (scaleInterval == 6) ? 0 : scaleInterval + 1;
                currentNote += LYDIAN_INTERVALS[scaleInterval];
            }

            notePartition.push_back(currentNote);
            modulationIndexPartition.push_back(modIndexMin + deltaMod * i);
        }
    }
private:
    std::vector<int> notePartition;
    std::vector<int> discreteModulationPartition;

    std::vector<float> realModulationPartition;
    std::vector<float> modulationIndexPartition;
    std::vector<float> amplitudePartition;

    int relativeModulationInterval = -4;

    int currentNote = 0;

    SpacePartition leapPartition;
    PhaseModulationStream pmStream;
};

#endif /* end of include guard: SYNTHCONTROLLER_H */
