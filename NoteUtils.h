#ifndef NOTE_UTILS_H
#define NOTE_UTILS_H

#include <cmath>
#include <cstring>

const static float twopi = (M_PI * 2);
const static float A4 = 440.f;
const static short SHORT_SCALE = 32767;

const int IONIAN_INTERVALS[] =     {2, 2, 1, 2, 2, 2, 1};
const int AEOLIAN_INTERVALS[] =    {2, 1, 2, 2, 1, 2, 2};
const int DORIAN_INTERVALS[] =     {2, 1, 2, 2, 2, 1, 2};
const int PHRYGIAN_INTERVALS[] =   {1, 2, 2, 1, 2, 2, 2};
const int LYDIAN_INTERVALS[] =     {2, 2, 2, 1, 2, 2, 1};
const int MIXOLYDIAN_INTERVALS[] = {2, 2, 1, 2, 2, 1, 2};
const int LOCRIAN_INTERVALS[] =    {1, 2, 2, 1, 2, 2, 2};

const int SCALE_SIZE = 7;

float getFrequency(int halfStepsFromA4)
{
    float power = (float)halfStepsFromA4/12.f;

    return A4 * (float)(std::pow(2, power));
}

const int* getModeIntervals(const char *name)
{
    if (std::strncmp(name, "major", 5) || std::strncmp(name, "ionian", 5))
    {
        return IONIAN_INTERVALS;
    }
    else if (std::strncmp(name, "minor", 5) || std::strncmp(name, "aeolian", 5))
    {
        return AEOLIAN_INTERVALS;
    }
    else if (std::strncmp(name, "dorian", 5))
    {
        return DORIAN_INTERVALS;
    }
    else if (std::strncmp(name, "phrygian", 5))
    {
        return PHRYGIAN_INTERVALS;
    }
    else if (std::strncmp(name, "lydian", 5))
    {
        return LYDIAN_INTERVALS;
    }
    else if (std::strncmp(name, "mixolydian", 5))
    {
        return MIXOLYDIAN_INTERVALS;
    }
    else if (std::strncmp(name, "locrian", 5))
    {
        return LOCRIAN_INTERVALS;
    }
    else {
        return nullptr;
    }
}

#endif /* end of include guard: NOTE_UTILS_H */
