/*
 * Copyright 2020 arsi.sk
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef EXTRUDER_H
#define EXTRUDER_H
#include <Arduino.h>
#include <avr/pgmspace.h>

class Extruder {
public:
    Extruder(const uint8_t stepPin, const uint8_t dirPin, const uint8_t enablePin, const float stepsPerMm, const float acceleration, const uint8_t isrKoef,const boolean revert);
    void timer_isr();
    void enableMotor();
    void didableMotor();
    void move(int mm);
    float getStepsPerMm();
    void setStepsPerMm(float stepsPerMm);
    float getAcceleration();
    void setAcceleration(float acceleration);
    uint8_t getIsrKoef();
    void setIsrKoef(uint8_t isrKoef);
    boolean isRevert();
    void setRevert(boolean revert);
    
    uint32_t getStepsToDo();

    enum Direction {
        STOPPED,
        TO_DIRECT_EXTRUDER,
        FROM_DIRECT_EXTRUDER

    };
    Direction getStatus();
    
private:
    volatile boolean revert;
    volatile Direction direction;
    volatile uint8_t dirPin;
    volatile uint8_t stepPin;
    volatile uint8_t enablePin;

    volatile uint16_t counter;
    volatile uint8_t isrCounter;
    volatile uint8_t isrKoef;

    volatile uint16_t brakeTripPoint;
    volatile uint16_t fullSeedTripPoint;

    volatile float acceleration;


    volatile uint32_t stepsToDo;
    volatile uint32_t stepsCurCount;


    volatile uint8_t stepBitMask;
    volatile uint8_t *stepPortRegister;

    volatile float stepsPerMm;

    volatile const PROGMEM float accelerationCurve[46] = {1,
        1,
        0.5,
        0.333333333333333,
        0.25,
        0.2,
        0.166666666666667,
        0.125,
        0.1,
        0.090909090909091,
        0.076923076923077,
        0.0625,
        0.055555555555556,
        0.05,
        0.043478260869565,
        0.038461538461539,
        0.03448275862069,
        0.03125,
        0.028571428571429,
        0.025641025641026,
        0.023809523809524,
        0.021739130434783,
        0.02,
        0.018518518518519,
        0.017241379310345,
        0.016393442622951,
        0.015384615384615,
        0.014705882352941,
        0.014084507042254,
        0.013513513513514,
        0.012987012987013,
        0.0125,
        0.01219512195122,
        0.011904761904762,
        0.011494252873563,
        0.01123595505618,
        0.011111111111111,
        0.010869565217391,
        0.010638297872341,
        0.010526315789474,
        0.010416666666667,
        0.010309278350516,
        0.010204081632653,
        0.01010101010101,
        0.01010101010101,
        0.01};
protected:

};

#endif /* EXTRUDER_H */

