
//
//  sinewave.h
//  Synth
//
//  Created by Wyatt Arent on 6/30/18.
//

#ifndef sinewave_h
#define sinewave_h


#endif /* sinewave_h */

#pragma once

using namespace stk;

struct SineWaveSound : public SynthesiserSound {
    SineWaveSound() {}
    
    bool appliesToNote      (int) override { return true; }
    bool appliesToChannel   (int) override { return true; }
};

struct SineWaveVoice : public SynthesiserVoice {
    SineWaveVoice() : adsr() {
        adsr.setAttackTime(0.1);
        adsr.setDecayTime(0.5);
        adsr.setSustainLevel(0.1);
        adsr.setReleaseTime(1);
        adsr.setReleaseRate(0.1);
    }
    
    bool canPlaySound (SynthesiserSound* sound) override {
        return dynamic_cast<SineWaveSound*> (sound) != nullptr;
    }
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int pitchWheelPosition) override {
        
        currentAngle = 0.0;
        level = velocity * 0.15;
        tailOff = 0.0;
        
        auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        sineWaveGenerator.setFrequency(cyclesPerSecond);
        
        adsr.setTarget(velocity);
        adsr.keyOn();
    }
    
    void stopNote (float velocity, bool allowTailOff) override {
        adsr.keyOff();
    }
    
    void pitchWheelMoved (int) override      {}
    void controllerMoved (int, int) override {}
    
    void renderNextBlock (AudioBuffer<float>& buffer, int startSample, int numSamples) override {
        if (adsr.getState() == ADSR::IDLE) {
            clearCurrentNote();
        } else {
            for (auto sample = 0; sample < buffer.getNumSamples(); sample++) {
                auto writeValue = sineWaveGenerator.tick() * adsr.tick();
                for (auto chan = 0; chan < buffer.getNumChannels(); chan++) {
                    buffer.addSample(chan, sample, writeValue);
                }
            }
        }
    }
    
private:
    double currentAngle, angleDelta, level, tailOff = 0.0;
    SineWave sineWaveGenerator;
    ADSR adsr;
};
