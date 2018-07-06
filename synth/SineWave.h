/*
 ==============================================================================
 Gemstone, a polyphonic step-sequenced sound synthesizer.
 Copyright (C) 2018 Wyatt Arent
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as
 published by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.
 
 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ==============================================================================
 */

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
    SineWaveVoice(SynthAudioProcessor& p) : processor(p), adsr() {
    }
    
    bool canPlaySound (SynthesiserSound* sound) override {
        return dynamic_cast<SineWaveSound*> (sound) != nullptr;
    }
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int pitchWheelPosition) override {

        level = velocity * 0.15;
        
        auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        sineWaveGenerator.setFrequency(cyclesPerSecond);
        
        adsr.setAttackTime(processor.attackTime);
        adsr.setDecayTime(processor.decayTime);
        adsr.setSustainLevel(processor.sustainLevel);
        adsr.setReleaseTime(processor.releaseTime);

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
                auto writeValue = sineWaveGenerator.tick() * adsr.tick() * level;
                for (auto chan = 0; chan < buffer.getNumChannels(); chan++) {
                    buffer.addSample(chan, sample, writeValue);
                }
            }
        }
    }
    
private:
    double level = 0.0;
    SineWave sineWaveGenerator;
    ADSR adsr;
    SynthAudioProcessor& processor;
};
