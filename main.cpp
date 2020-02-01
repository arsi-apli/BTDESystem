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
#include "BtdeController.h"


extern HardwareSerial Serial;
extern HardwareSerial Serial2;


//BTDESystem
#define BTDE_VERSION "1.0 Beta"
//



 BtdeController controller;



ISR(TIMER1_COMPA_vect) {
   controller.timerIsr();
}

ISR(TIMER3_COMPA_vect) {
    controller.endStopsIsr();

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
    Serial.println("\033[2J");
    Serial.println(F("****************************************************************************"));
    Serial.print(F("BTDESystem "));
    Serial.println(F(BTDE_VERSION));
    Serial.println(F("****************************************************************************"));
    Serial.print(F("Config loaded from EEPROM: "));
    if (controller.isLoadedFromEeprom()) {
        Serial.println(F("YES"));
    } else {
        Serial.println(F("NO"));
    }

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

    controller.initSystem();
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

void usbShowStatus() {
    Serial.println("\033[2J");
    Serial.println(F("****************************************************************************"));
    Serial.print(F("BTDESystem "));
    Serial.println(F(BTDE_VERSION));
    Serial.println(F("****************************************************************************"));
    Serial.print(F("Active extruder: "));
    Serial.println(controller.getCurrentExtruderName());
    Serial.println(F("****************************************************************************"));
    Serial.println(F("To continue press enter"));
}

void usbEjectFromBowden() {
    Serial.println("\033[2J");
    Serial.println(F("****************************************************************************"));
    Serial.print(F("BTDESystem "));
    Serial.println(F(BTDE_VERSION));
    Serial.println(F("****************************************************************************"));
    Serial.println(F("Eject filament from bowden extruder."));
    Serial.println(F("     Note that the filament must be pulled out from the direct extruder!"));
    Serial.println(F("****************************************************************************"));
    Serial.println(F("Enter extruder number to eject from 0-4"));
    while (!Serial.available());
    int c = Serial.read();
    switch (c) {
        case '0':
            Serial.println(F("Ejecting filament from bowden extruder 0"));
            break;
        case '1':
            Serial.println(F("Ejecting filament from bowden extruder 1"));
            break;
        case '2':
            Serial.println(F("Ejecting filament from bowden extruder 2"));
            break;
        case '3':
            Serial.println(F("Ejecting filament from bowden extruder 3"));
            break;
        case '4':
            Serial.println(F("Ejecting filament from bowden extruder 4"));
            break;
        default:
            Serial.println(F(" Error input. Supported numbers are 0,1,2,3,4"));
            Serial.println(F(" Press ENTER"));
            break;
    }
    Serial.read(); // skip  \n
}

void loop() {
    //Handle USB Serial port
    if (Serial.available() > 0) {
        int c = Serial.read();
        switch (c) {
            case 'E': //Ex eject filament from bowden extruder
            case 'e': //Ex eject filament from bowden extruder
                usbEjectFromBowden();
                break;
            case 'C': //Cx load filament into the bowden extruder and push it in half of compensator
            case 'c': //Cx load filament into the bowden extruder and push it in half of compensator
                // as next, user must manually introduce the filament into the carriage
                break;
            case 'L': //Lx load filament into inactive position in joiner, from half of compensator
            case 'l': //Lx load filament into inactive position in joiner, from half of compensator
                break;
            case 'T': //Tx load the filament into the direct extruder idler.
            case 't': //Tx load the filament into the direct extruder idler.
                break;
            case 'I': //Ix unload the filament from the direct extruder to inactive position in joiner.
            case 'i': //Ix unload the filament from the direct extruder to inactive position in joiner.
                break;
            case '?': //Show current status. 
                usbShowStatus();
                break;
            default:
                printUsbHelp();
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

