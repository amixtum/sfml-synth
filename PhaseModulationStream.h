#ifndef PHASE_MODULATION_STREAM_H
#define PHASE_MODULATION_STREAM_H

#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>

class PhaseModulationStream : public sf::SoundStream
{
public:
    PhaseModulationStream()
    {
        initialize(channelCount, sampleRate);
        carrierIncrement = (twopi * carrierFrequency) / (float)sampleRate;
        modulationIncrement = (twopi * modulationFrequency) / (float)sampleRate;
    }
    ~PhaseModulationStream() {}

    void setCarrierFrequency(float frequency)
    {
        carrierFrequency = frequency;
        carrierIncrement = (twopi * carrierFrequency) / (float)sampleRate;
    }

    void lerpToCarrierFrequency(float frequency, float amount)
    {
        float newFrequency = lerp(carrierFrequency, frequency, amount);
        setCarrierFrequency(newFrequency);
    }

    void coserpToCarrierFrequency(float frequency, float amount)
    {
        float newFrequency = coserp(carrierFrequency, frequency, amount);
        setCarrierFrequency(newFrequency);
    }

    void cuberpToCarrierFrequency(float frequency, float inter1,
                                  float inter2, float amount)
    {
        float newFrequency = cuberp(carrierFrequency, inter1,
                                    inter2, frequency, amount);
        setCarrierFrequency(newFrequency);
    }

    void setModulationFrequency(float frequency)
    {
        modulationFrequency = frequency;
        modulationIncrement = (twopi * modulationFrequency) / (float)sampleRate;
    }

    void lerpToModulationFrequency(float frequency, float amount)
    {
        float newFrequency = lerp(modulationFrequency, frequency, amount);
        setModulationFrequency(newFrequency);
    }

    void coserpToModulationFrequency(float frequency, float amount)
    {
        float newFrequency = coserp(modulationFrequency, frequency, amount);
        setModulationFrequency(newFrequency);
    }

    void cuberpToModulationFrequency(float frequency, float inter1,
                                  float inter2, float amount)
    {
        float newFrequency = cuberp(modulationFrequency, inter1,
                                    inter2, frequency, amount);
        setModulationFrequency(newFrequency);
    }

    void setCarrierNote(int halfStepsFromA4)
    {
        coserpToCarrierFrequency(getFrequency(halfStepsFromA4),
                                 interpolationSpeed);
    }

    void setCarrierNote(int halfStepsFromA4, int interNote1, int interNote2)
    {
        cuberpToCarrierFrequency(getFrequency(halfStepsFromA4),
                                 interNote1, interNote2, interpolationSpeed);
    }

    void setModulationNote(int halfStepsFromA4)
    {
        coserpToModulationFrequency(getFrequency(halfStepsFromA4),
                                    interpolationSpeed);
    }

    void setModulationNote(int halfStepsFromA4, int interNote1, int interNote2)
    {
        cuberpToModulationFrequency(getFrequency(halfStepsFromA4),
                                 interNote1, interNote2, interpolationSpeed);
    }

    void setModulationIndex(float modIndex)
    {
        modulationIndex = modIndex;
    }

    void setAmplitude(float amp)
    {
        backupAmplitude = amplitude;

        if (amp > 1.0)
        {
            amplitude = 1.0;
        }
        else if (amp < 0)
        {
            amplitude = 0;
        }
        else
        {
            amplitude = amp;
        }
    }

    void turnOn()
    {
        amplitude = backupAmplitude;
    }

    void turnOff()
    {
        setAmplitude(0);
    }

    void setInterpolationSpeed(float speed)
    {
        interpolationSpeed = speed;
    }
private:
    virtual bool onGetData(sf::SoundStream::Chunk &data)
    {
        buffer.reserve(chunkSize);

        for (int i = 0; i < chunkSize; ++i)
        {
            buffer.push_back((short)(amplitude *
                                     SHORT_SCALE *
                                     compute()));
        }

        data.samples = &buffer[0];

        data.sampleCount = chunkSize;

        buffer.clear();

        return true;
    }

    virtual void onSeek (sf::Time timeOffset)
    {
        return;
    }

    float lerp(float current, float target, float amount)
    {
        return current + (target - current) * amount;
    }

    float coserp(float current, float target, float amount)
    {
        float amount2 = (float)(1.f - std::cos(amount * M_PI)) / 2.f;

        return current + (target - current) * amount2;
    }

    float cuberp(float current, float inter1, float inter2,
                 float target, float amount)
    {
        float amount2 = amount * amount;
        float a0 = target - inter2 - current + inter1;
        float a1 = current - inter1 - a0;
        float a2 = inter2 - current;
        float a3 = inter1;

        return (a0*amount*amount2+a1*amount2+a2*amount+a3);
    }

    void incrementCarrierPhase()
    {
        carrierPhase += carrierIncrement;

        if (carrierPhase >= twopi) carrierPhase -= twopi;
        if (carrierPhase < 0) carrierPhase += twopi;
    }

    void incrementModulationPhase()
    {
        modulationPhase += modulationIncrement;

        if (modulationPhase >= twopi) modulationPhase -= twopi;
        if (modulationPhase < 0) modulationPhase += twopi;
    }

    float compute()
    {
        float val = (float)(std::sin(carrierPhase + modulationIndex *
                                             std::cos(modulationPhase)));

        incrementCarrierPhase();
        incrementModulationPhase();

        return val;
    }
private:
    float interpolationSpeed = 0.25f;

    float carrierIncrement;
    float carrierFrequency = A4;

    float currentCarrierNote = 0;

    float modulationIndex = 0;
    float modulationIncrement;
    float modulationFrequency = 0;

    float currentModulationNote = 0;

    float carrierPhase = 0.0;
    float modulationPhase = 0.0;

    float amplitude = 0.5f;
    float backupAmplitude = 0.5f;

    int chunkSize = 1024;
    std::vector<short> buffer;

    unsigned int channelCount = 1;
    unsigned int sampleRate = 44100;
};

#endif /* end of include guard:  PHASE_MODULATION_STREAM_H*/
