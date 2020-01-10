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

#include "Extruder.h"

#define ROUNDED_INT(f) ((int32_t)(f >= 0.0f ? (f + 0.5f) : (f - 0.5f)))
#define LENGTH(a) (sizeof(a)/sizeof(*a))
Extruder::Extruder(const uint8_t stepPin, const uint8_t dirPin, const uint8_t enablePin, const float stepsPerMm, const float acceleration, const uint8_t isrKoef, const boolean revert) {
    this->stepPin = stepPin;
    this->dirPin = dirPin;
    this->enablePin = enablePin;
    this->stepsPerMm = stepsPerMm;
    this->acceleration = acceleration;
    this->stepsToDo = 0;
    this->isrKoef = isrKoef;
    this->direction = STOPPED;
    this->revert = revert;
    pinMode(stepPin, OUTPUT); //led
    pinMode(dirPin, OUTPUT); //led
    pinMode(enablePin, OUTPUT); //led
    digitalWrite(dirPin, HIGH);
    digitalWrite(enablePin, HIGH);
    stepBitMask = digitalPinToBitMask(stepPin);
    stepPortRegister = portOutputRegister(digitalPinToPort(stepPin));
    *stepPortRegister &= ~stepBitMask; // Pin to LOW
}

void Extruder::enableMotor() {
    digitalWrite(enablePin, LOW);
}

void Extruder::didableMotor() {
    digitalWrite(enablePin, HIGH);
}

void Extruder::move(int mm) {
    noInterrupts(); // disable all interrupts
    if (mm == 0) {
        return;
    } else if (mm > 0) {
        if (!revert) {
            digitalWrite(dirPin, HIGH);
        } else {
            digitalWrite(dirPin, LOW);
        }

        direction = FROM_DIRECT_EXTRUDER;
    } else {
        if (!revert) {
            digitalWrite(dirPin, LOW);
        } else {
            digitalWrite(dirPin, HIGH);
        }

        direction = TO_DIRECT_EXTRUDER;
    }
    stepsCurCount = 0;
    stepsToDo = abs(mm) * stepsPerMm;

    if (sizeof (accelerationCurve) * 2 <= stepsToDo) {
        brakeTripPoint = fullSeedTripPoint = LENGTH(accelerationCurve);
    } else {
        brakeTripPoint = stepsToDo / 2;
        fullSeedTripPoint = stepsToDo / 2;
    }
    counter = ROUNDED_INT(acceleration * accelerationCurve[0]);
    interrupts(); // enable all interrupts
}

Extruder::Direction Extruder::getStatus() {
    return direction;
}

void Extruder::timer_isr() {
    if (isrCounter > 0) {
        isrCounter--;
        return;
    } else {
        isrCounter = isrKoef;
    }
    if (stepsToDo > 0) {
        if (counter > 0) {
            counter--;
            return;
        }
        if (stepsCurCount <= fullSeedTripPoint) {
            if (stepsCurCount + 1 <= LENGTH(accelerationCurve) - 1) {
                counter = ROUNDED_INT(acceleration * accelerationCurve[stepsCurCount + 1]);
            }
        } else if (stepsToDo <= brakeTripPoint) {
            if (stepsToDo - 1 <= LENGTH(accelerationCurve) - 1) {
                counter = ROUNDED_INT(acceleration * accelerationCurve[stepsToDo - 1]);
            } else {
                counter = ROUNDED_INT(acceleration * accelerationCurve[0]);
            }
        }
        stepsToDo--;
        stepsCurCount++;
        *stepPortRegister &= ~stepBitMask; // Pin to LOW
        *stepPortRegister |= stepBitMask; // Pin to HIGH
    } else {
        direction = STOPPED;
    }
}
    //---------------------getters--setters----------------------
    
    float Extruder::getStepsPerMm(){
        return this->stepsPerMm;
    }
    void Extruder::setStepsPerMm(float stepsPerMm){
        this->stepsPerMm = stepsPerMm;
    }
    float Extruder::getAcceleration(){
        return this->acceleration;
    }
    void Extruder::setAcceleration(float acceleration){
        this->acceleration = acceleration;
    }
    uint8_t Extruder::getIsrKoef(){
        return this->isrKoef;
    }
    void Extruder::setIsrKoef(uint8_t isrKoef){
        this->isrKoef = isrKoef;
    }
    boolean Extruder::isRevert(){
        return this->revert;
    }
    void Extruder::setRevert(boolean revert){
        this->revert = revert;
    }
    
    uint32_t Extruder::getStepsToDo(){
        return this->stepsToDo;
    }


