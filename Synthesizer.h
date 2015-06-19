#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <SFML/Audio.hpp>
#include <cmath>
#include <memory>
#include <vector>

#include "NoteUtils.h"

class SineSynthesizer
{
public:
    SineSynthesizer() : SineSynthesizer(440.f) { }

    ~SineSynthesizer()
    {
        delete samples;
    }

    // start note is defined
    // as the number of half steps from A4
    std::vector<std::unique_ptr<sf::Sound>> getScale(int startNote,
                                                     int numIntervals,
                                                     const char* modeName)
    {
        const int *intervals = getModeIntervals(modeName);

        std::vector<std::unique_ptr<sf::Sound>> scaleVector;
        scaleVector.reserve(numIntervals);

        if (intervals != nullptr)
        {
            int note = startNote;
            int currentInterval = 0;

            for (int i = 0; i < numIntervals; ++i)
            {
                auto soundPtr = getSound(note);

                scaleVector.push_back(std::move(soundPtr));

                note += currentInterval;

                currentInterval = (currentInterval == SCALE_SIZE - 1) ?
                                   0 :
                                   currentInterval + 1;
            }
        }

        return scaleVector;
    }

    std::unique_ptr<sf::Sound> getSound()
    {
        return getSound(0, 100);
    }

    std::unique_ptr<sf::Sound> getSound(int halfStepsFromA4)
    {
        return getSound(halfStepsFromA4, 100);
    }

    std::unique_ptr<sf::Sound> getSound(int halfStepsFromA4, float volume)
    {
        std::unique_ptr<sf::Sound> soundPtr(new sf::Sound());

        soundPtr->setLoop(true);

        soundPtr->setBuffer(buffer);

        float frequencyRatio = getFrequency(halfStepsFromA4) / A4;

        soundPtr->setPitch(frequencyRatio);

        soundPtr->setVolume(volume);

        return soundPtr;
    }
private:
    SineSynthesizer(float initialFrequency)
    {
        samples = new short[sampleCount];
        
        float increment = (float)((twopi * initialFrequency) / sampleRate);
        float phase = 0;

        for (int i = 0; i < (int)sampleCount; ++i)
        {
            samples[i] = (short)(SHORT_SCALE * amplitude * std::sin(phase));

            phase += increment;

            if (phase >= twopi) phase -= twopi;
            if (phase < 0) phase += twopi;
        }

        buffer.loadFromSamples(samples, sampleCount, channelCount, sampleRate);
    }
private:
    sf::SoundBuffer buffer;
    unsigned int sampleRate = 44100;
    unsigned int channelCount = 1;
    unsigned long sampleCount = 44100;
    float amplitude = 0.5f;
    short *samples;
};

#endif /* end of include guard: SYNTHESIZER_H  */
