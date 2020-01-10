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
#include <Arduino.h>
#include <avr/io.h>
#include "Extruder.h"

extern HardwareSerial Serial;

//-------------------------------------------------------------------------
#define ENDSTOP_FEED_LENGTH 15// Length of filament retracted/pushed on endstop hit

//--------------Extruders--------------------------------------------------
#define ETRUDER_X_STEPS_PER_MM 391
#define ETRUDER_X_ACCELERATION 500 // 20kHz/(acceleration*hardcoded curve)
#define ETRUDER_X_MAX_SPEED 0 // 0-20kHz, 1-10kHz, 2-5kHz ...
#define ETRUDER_X_REVERSE true

#define ETRUDER_Y_STEPS_PER_MM 391
#define ETRUDER_Y_ACCELERATION 500 // 20kHz/(acceleration*hardcoded curve)
#define ETRUDER_Y_MAX_SPEED 0 // 0-20kHz, 1-10kHz, 2-5kHz ...
#define ETRUDER_Y_REVERSE true

#define ETRUDER_Z_STEPS_PER_MM 391
#define ETRUDER_Z_ACCELERATION 500 // 20kHz/(acceleration*hardcoded curve)
#define ETRUDER_Z_MAX_SPEED 0 // 0-20kHz, 1-10kHz, 2-5kHz ...
#define ETRUDER_Z_REVERSE true

#define ETRUDER_E0_STEPS_PER_MM 391
#define ETRUDER_E0_ACCELERATION 500 // 20kHz/(acceleration*hardcoded curve)
#define ETRUDER_E0_MAX_SPEED 0 // 0-20kHz, 1-10kHz, 2-5kHz ...
#define ETRUDER_E0_REVERSE true

#define ETRUDER_E1_STEPS_PER_MM 391
#define ETRUDER_E1_ACCELERATION 500 // 20kHz/(acceleration*hardcoded curve)
#define ETRUDER_E1_MAX_SPEED 0 // 0-20kHz, 1-10kHz, 2-5kHz ...
#define ETRUDER_E1_REVERSE true


//-----------------------pins---------------------
#define STEPPER_E0_DIR 28
#define STEPPER_E0_STEP 26
#define STEPPER_E0_ENABLE 24
#define STEPPER_E0_MICRO_STEPS 16
#define STEPPER_E0_RPM 2500

#define STEPPER_E1_DIR 34
#define STEPPER_E1_STEP 36
#define STEPPER_E1_ENABLE 30
#define STEPPER_E1_MICRO_STEPS 16
#define STEPPER_E1_RPM 2500

#define STEPPER_X_DIR 55
#define STEPPER_X_STEP 54
#define STEPPER_X_ENABLE 38
#define STEPPER_X_MICRO_STEPS 16
#define STEPPER_X_RPM 2500

#define STEPPER_Y_DIR 61
#define STEPPER_Y_STEP 60
#define STEPPER_Y_ENABLE 56
#define STEPPER_Y_MICRO_STEPS 16
#define STEPPER_Y_RPM 2500

#define STEPPER_Z_DIR 48
#define STEPPER_Z_STEP 46
#define STEPPER_Z_ENABLE 62
#define STEPPER_Z_MICRO_STEPS 16
#define STEPPER_Z_RPM 2500

#define PIN_X_MIN 3
#define PIN_X_MAX 2

#define PIN_Y_MIN 14
#define PIN_Y_MAX 15

#define PIN_Z_MIN 18
#define PIN_Z_MAX 19


#define PIN_LED 13


#define SERIAL_BAUDRATE 115200

enum Extruders {
    EXTRUDER_X,
    EXTRUDER_Y,
    EXTRUDER_Z,
    EXTRUDER_E0,
    EXTRUDER_E1,
};

static volatile Extruders currentExtruder = EXTRUDER_X;


Extruder stepperX(STEPPER_X_STEP, STEPPER_X_DIR, STEPPER_X_ENABLE, ETRUDER_X_STEPS_PER_MM, ETRUDER_X_ACCELERATION, ETRUDER_X_MAX_SPEED, ETRUDER_X_REVERSE);
Extruder stepperY(STEPPER_Y_STEP, STEPPER_Y_DIR, STEPPER_Y_ENABLE, ETRUDER_Y_STEPS_PER_MM, ETRUDER_Y_ACCELERATION, ETRUDER_Y_MAX_SPEED, ETRUDER_Y_REVERSE);
Extruder stepperZ(STEPPER_Z_STEP, STEPPER_Z_DIR, STEPPER_Z_ENABLE, ETRUDER_Z_STEPS_PER_MM, ETRUDER_Z_ACCELERATION, ETRUDER_Z_MAX_SPEED, ETRUDER_Z_REVERSE);
Extruder stepperE0(STEPPER_E0_STEP, STEPPER_E0_DIR, STEPPER_E0_ENABLE, ETRUDER_E0_STEPS_PER_MM, ETRUDER_E0_ACCELERATION, ETRUDER_E0_MAX_SPEED, ETRUDER_E0_REVERSE);
Extruder stepperE1(STEPPER_E1_STEP, STEPPER_E1_DIR, STEPPER_E1_ENABLE, ETRUDER_E1_STEPS_PER_MM, ETRUDER_E1_ACCELERATION, ETRUDER_E1_MAX_SPEED, ETRUDER_E1_REVERSE);

ISR(TIMER1_COMPA_vect) {
    switch (currentExtruder) {
        case EXTRUDER_X:
            stepperX.timer_isr();
            break;
        case EXTRUDER_Y:
            stepperY.timer_isr();
            break;
        case EXTRUDER_Z:
            stepperZ.timer_isr();
            break;
    }
}

ISR(TIMER3_COMPA_vect) {
    switch (currentExtruder) {
        case EXTRUDER_X:
            if (digitalRead(PIN_X_MAX) == 0) {
                if (stepperX.getStatus() != Extruder::FROM_DIRECT_EXTRUDER) {
                    stepperX.move(ENDSTOP_FEED_LENGTH);
                }
            } else if (digitalRead(PIN_X_MIN) == 0) {
                if (stepperX.getStatus() != Extruder::TO_DIRECT_EXTRUDER) {
                    stepperX.move(-ENDSTOP_FEED_LENGTH);
                }
            }
            break;
        case EXTRUDER_Y:
            if (digitalRead(PIN_Y_MAX) == 0) {
                if (stepperY.getStatus() != Extruder::FROM_DIRECT_EXTRUDER) {
                    stepperY.move(ENDSTOP_FEED_LENGTH);
                }
            } else if (digitalRead(PIN_Y_MIN) == 0) {
                if (stepperY.getStatus() != Extruder::TO_DIRECT_EXTRUDER) {
                    stepperY.move(-ENDSTOP_FEED_LENGTH);
                }
            }
            break;
        case EXTRUDER_Z:
            if (digitalRead(PIN_Z_MAX) == 0) {
                if (stepperZ.getStatus() != Extruder::FROM_DIRECT_EXTRUDER) {
                    stepperZ.move(ENDSTOP_FEED_LENGTH);
                }
            } else if (digitalRead(PIN_Z_MIN) == 0) {
                if (stepperZ.getStatus() != Extruder::TO_DIRECT_EXTRUDER) {
                    stepperZ.move(-ENDSTOP_FEED_LENGTH);
                }
            }
            break;
    }

}

void setupTimer1() {
    noInterrupts();
    // Clear registers
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    // 20000 Hz (16000000/((99+1)*8))
    OCR1A = 99;
    // CTC
    TCCR1B |= (1 << WGM12);
    // Prescaler 8
    TCCR1B |= (1 << CS11);
    // Output Compare Match A Interrupt Enable
    TIMSK1 |= (1 << OCIE1A);
    interrupts();
}

void setupTimer3() {
    noInterrupts();
    // Clear registers
    TCCR3A = 0;
    TCCR3B = 0;
    TCNT3 = 0;

    // 10 Hz (16000000/((6249+1)*256))
    OCR3A = 6249;
    // CTC
    TCCR3B |= (1 << WGM32);
    // Prescaler 256
    TCCR3B |= (1 << CS32);
    // Output Compare Match A Interrupt Enable
    TIMSK3 |= (1 << OCIE3A);
    interrupts();
}

void setup() {
    Serial.begin(SERIAL_BAUDRATE);
    pinMode(PIN_LED, OUTPUT); //led

    pinMode(PIN_X_MIN, INPUT);
    pinMode(PIN_X_MAX, INPUT);

    pinMode(PIN_Y_MIN, INPUT);
    pinMode(PIN_Y_MAX, INPUT);

    pinMode(PIN_Z_MIN, INPUT);
    pinMode(PIN_Z_MAX, INPUT);

    stepperX.enableMotor();
    setupTimer1();
    setupTimer3();

}

void loop() {
}

