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
extern HardwareSerial Serial2;

//-------------------------------------------------------------------------
#define ENDSTOP_FEED_LENGTH 15// Length of filament retracted/pushed on endstop hit
#define BOWDEN_EXTRUDER_TO_COMPENSATOR_TUBE_LENGTH 500 //PTFE tube length in mm
#define COMPENSATOR_LENGTH 90 //Length of compensator including quick connectors
#define COMPENSATOR_TO_JOINER_TUBE_LENGTH 200 // PTFE tube length in mm + mm to inactive filament position in joiner
#define JOINER_INACTIVE_POSITION_TO_DIRECT_EXTRUDER 25 // Length from inactive position in joiner to direct extruder in mm

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

//MMU2
#define FW_VERSION 90            
#define FW_BUILDNR 168
//BTDESystem
#define BTDE_VERSION "1.0 Beta"
//

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

void printUsbHelp() {
    Serial.println(F("****************************************************************************"));
    Serial.println(F("E0-E4 eject filament from bowden extruder."));
    Serial.println(F("     Note that the filament must be pulled out from the direct extruder!"));
    Serial.println();
    Serial.println(F("C0-C4 load filament from bowden extruder to half of compensator."));
    Serial.println(F("     Note that as next, you must manually introduce the filament into the carriage"));
    Serial.println();
    Serial.println(F("L0-L4 load filament from half of compensator to inactive position in joiner"));
    Serial.println();
    Serial.println(F("I0-I4 unload the filament from the direct extruder to inactive position in joiner."));
    Serial.println(F("     Note that the filament must be pulled out from the direct extruder!"));
    Serial.println();
    Serial.println(F("T0-T4 load the filament into the direct extruder idler."));
    Serial.println(F("     Note that as next, must direct extruder load the filament"));
    Serial.println();
    Serial.println(F("? Show curent filaments/extruders status"));
    Serial.println();
    Serial.println(F("****************************************************************************"));
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
    Serial2.begin(SERIAL_BAUDRATE);
    delay(100);
    Serial.print(F("BTDESystem "));
    Serial.println(F(BTDE_VERSION));
    Serial.println(F("Sending START command to Marlin"));
    printUsbHelp();
    Serial2.print(F("start\n")); // attempt to tell the mk3 that the mmu is present
}

void handleFirmwareInfo() {
    unsigned char c = Serial2.read();
    switch (c) {
        case '0':
            Serial2.print(F("ok\n"));
            Serial.println(F("S0"));
            break;
        case '1':
            Serial2.print(FW_VERSION);
            Serial2.print(F("ok\n"));
            Serial.println(F("S1"));
            break;
        case '2':
            Serial2.print(FW_BUILDNR);
            Serial2.print(F("ok\n"));
            Serial.println(F("S2"));
            break;
        default:
            Serial.print(F("S"));
            Serial.print(c);
            Serial.println(F(" Error response from marlin"));
            break;
    }
    Serial2.read(); // skip  \n
}

void handle12vMode() {
    unsigned char c = Serial2.read();
    switch (c) {
        case '1':
            Serial2.print(F("ok\n"));
            Serial.println(F("M1"));
            break;
        default:
            Serial.print(F("M"));
            Serial.print(c);
            Serial.println(F(" Error response from marlin"));
            break;
    }
    Serial2.read(); // skip  \n
}

void handleFindaStatus() {
    unsigned char c = Serial2.read();
    switch (c) {
        case '0':
            Serial2.print(F("1"));
            Serial2.print(F("ok\n"));
            Serial.println(F("P0"));
            break;
        default:
            Serial.print(F("P"));
            Serial.print(c);
            Serial.println(F(" Error response from marlin"));
            break;
    }
    Serial2.read(); // skip  \n
}

void handleFilamentType() {
    unsigned char c = Serial2.read();
    switch (c) {
        default:
            Serial2.print(F("ok\n"));
            Serial.println(F("Handle filament type..."));
            break;
    }
    Serial2.read(); // skip  \n
}

void handleToolChange() {
    unsigned char c = Serial2.read();
    switch (c) {
        case '0':
            Serial2.print(F("ok\n"));
            Serial.println(F("T0"));
            break;
        case '1':
            Serial2.print(F("ok\n"));
            Serial.println(F("T1"));
            break;
        case '2':
            Serial2.print(F("ok\n"));
            Serial.println(F("T2"));
            break;
        case '3':
            Serial2.print(F("ok\n"));
            Serial.println(F("T3"));
            break;
        case '4':
            Serial2.print(F("ok\n"));
            Serial.println(F("T4"));
            break;
        default:
            Serial.print(F("T"));
            Serial.print(c);
            Serial.println(F(" Error response from marlin"));
            break;
    }
    Serial2.read(); // skip  \n
}

void handleToolChangeFeedToExtruder() {
    unsigned char c = Serial2.read();
    switch (c) {
        case '0':
            Serial2.print(F("ok\n"));
            Serial.println(F("C0"));
            break;
        default:
            Serial.print(F("C"));
            Serial.print(c);
            Serial.println(F(" Error response from marlin"));
            break;
    }
    Serial2.read(); // skip  \n
}

void handleLoadFilament() {
    unsigned char c = Serial2.read();
    switch (c) {
        case '0':
            Serial2.print(F("ok\n"));
            Serial.println(F("L0"));
            break;
        case '1':
            Serial2.print(F("ok\n"));
            Serial.println(F("L1"));
            break;
        case '2':
            Serial2.print(F("ok\n"));
            Serial.println(F("L2"));
            break;
        case '3':
            Serial2.print(F("ok\n"));
            Serial.println(F("L3"));
            break;
        case '4':
            Serial2.print(F("ok\n"));
            Serial.println(F("L4"));
            break;
        default:
            Serial.print(F("L"));
            Serial.print(c);
            Serial.println(F(" Error response from marlin"));
            break;
    }
    Serial2.read(); // skip  \n
}

void handleUnLoadFilament() {
    unsigned char c = Serial2.read();
    switch (c) {
        case '0':
            Serial2.print(F("ok\n"));
            Serial.println(F("U0"));
            break;
        case '1':
            Serial2.print(F("ok\n"));
            Serial.println(F("U1"));
            break;
        case '2':
            Serial2.print(F("ok\n"));
            Serial.println(F("U2"));
            break;
        case '3':
            Serial2.print(F("ok\n"));
            Serial.println(F("U3"));
            break;
        case '4':
            Serial2.print(F("ok\n"));
            Serial.println(F("U4"));
            break;
        default:
            Serial.print(F("U"));
            Serial.print(c);
            Serial.println(F(" Error response from marlin"));
            break;
    }
    Serial2.read(); // skip  \n
}

void handleEjectFilament() {
    unsigned char c = Serial2.read();
    switch (c) {
        case '0':
            Serial2.print(F("ok\n"));
            Serial.println(F("E0"));
            break;
        case '1':
            Serial2.print(F("ok\n"));
            Serial.println(F("E1"));
            break;
        case '2':
            Serial2.print(F("ok\n"));
            Serial.println(F("E2"));
            break;
        case '3':
            Serial2.print(F("ok\n"));
            Serial.println(F("E3"));
            break;
        case '4':
            Serial2.print(F("ok\n"));
            Serial.println(F("E4"));
            break;
        default:
            Serial.print(F("E"));
            Serial.print(c);
            Serial.println(F(" Error response from marlin"));
            break;
    }
    Serial2.read(); // skip  \n
}

void loop() {
    //Handle USB Serial port
    if (Serial.available() > 0) {
        unsigned char c = Serial2.read();
        switch (c) {
            case 'E': //Ex eject filament from bowden extruder
                break;
            case 'C': //Cx load filament into the bowden extruder and push it in half of compensator
                // as next, user must manually introduce the filament into the carriage
                break;
            case 'L': //Lx load filament into inactive position in joiner, from half of compensator
                break;
            case 'T': //Tx load the filament into the direct extruder idler.
                break;
            case 'I': //Ix unload the filament from the direct extruder to inactive position in joiner.
                break;
            case '?': //Show current status. 
                break;

        }
    }
    //handle Marlin serial port
    if (Serial2.available() > 0) {
        unsigned char c = Serial2.read();
        switch (c) {
            case 'S': //firmware info
                //                - MMU <= 'S0\n'
                //                - MMU = > 'ok\n'
                //                - MMU <= 'S1\n'
                //                - MMU = > 'ok*Firmware version*\n'
                //                - MMU <= 'S2\n'
                //                - MMU = > 'ok*Build number*\n'
                handleFirmwareInfo();
                break;
            case 'M': // 12V mode
                //                - MMU <= 'M1\n'
                //                - MMU => 'ok\n'
                handle12vMode();
                break;
            case 'P': //FINDA status
                //                - MMU <= 'P0\n'
                //                - MMU => '*FINDA status*\n'
                //                *FINDA status* is 1 if the is filament loaded to the extruder, 0 otherwise. This could be used as filament runout sensor if probed regularly.
                handleFindaStatus();
                break;
            case 'F':
                // 'F' command is acknowledged but no processing goes on at the moment
                // will be useful for flexible material down the road
                handleFilamentType();
                break;
            case 'T': //tool change
                //                - MMU <= 'T*Filament index*\n'
                //                MMU sends
                //                - MMU => 'ok\n'
                //                as soon as the filament is fed down to the extruder. We follow with
                //                - MMU <= 'C0\n'
                //                MMU will feed a few more millimeters of filament for the extruder gears to grab.
                //                When done, the MMU sends
                handleToolChange();
                break;
            case 'C': //feed a few more millimeters of filament for the extruder gears to grab.
                handleToolChangeFeedToExtruder();
                break;
            case 'L': //load filament
                //                - MMU <= 'L*Filament index*\n'
                //                MMU will feed filament down to the extruder, when done
                //                - MMU => 'ok\n'
                handleLoadFilament();
                break;
            case 'U': //unload filament
                //                - MMU <= 'U0\n'
                //                MMU will retract current filament from the extruder, when done
                //                - MMU => 'ok\n'
                handleUnLoadFilament();
                break;
            case 'E': //eject filament
                //                - MMU <= 'E*Filament index*\n'
                //                - MMU => 'ok\n'
                handleEjectFilament();
                break;
            default:
                Serial.print(F("Unknown command from Marlin received: "));
                Serial.print(c);
                break;

        }
    }
}

