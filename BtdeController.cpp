/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BtdeController.cpp
 * Author: arsi
 * 
 * Created on Sobota, 2020, februára 1, 22:38
 */

#include "BtdeController.h"

BtdeController::BtdeController() {
}

BtdeController::ExtrudersNames BtdeController::getCurrentExtruderName() {
    return this->systemConfig.currentExtruderName;
}

void BtdeController::timerIsr() {
    switch (this->systemConfig.currentExtruderName) {
        case EXTRUDER_X:
            extruders[EXTRUDER_X].timer_isr();
            break;
        case EXTRUDER_Y:
            extruders[EXTRUDER_Y].timer_isr();
            break;
        case EXTRUDER_Z:
            extruders[EXTRUDER_Z].timer_isr();
            break;
        case EXTRUDER_E0:
            extruders[EXTRUDER_E0].timer_isr();
            break;
        case EXTRUDER_E1:
            extruders[EXTRUDER_E1].timer_isr();
            break;
    }

}

void BtdeController::endStopsIsr() {
    switch (this->systemConfig.currentExtruderName) {
        case EXTRUDER_X:
            if (digitalRead(PIN_X_MAX) == 0) {
                extruders[EXTRUDER_X].move(ENDSTOP_FEED_LENGTH);
            } else if (digitalRead(PIN_X_MIN) == 0) {
                extruders[EXTRUDER_X].move(-ENDSTOP_FEED_LENGTH);
            }
            break;
        case EXTRUDER_Y:
            if (digitalRead(PIN_Y_MAX) == 0) {
                extruders[EXTRUDER_Y].move(ENDSTOP_FEED_LENGTH);
            } else if (digitalRead(PIN_Y_MIN) == 0) {
                extruders[EXTRUDER_Y].move(-ENDSTOP_FEED_LENGTH);
            }
            break;
        case EXTRUDER_Z:
            if (digitalRead(PIN_Z_MAX) == 0) {
                extruders[EXTRUDER_Z].move(ENDSTOP_FEED_LENGTH);
            } else if (digitalRead(PIN_Z_MIN) == 0) {
                extruders[EXTRUDER_Z].move(-ENDSTOP_FEED_LENGTH);
            }
            break;
        case EXTRUDER_E0:
            //            if (digitalRead(PIN_Z_MAX) == 0) {
            //                extruders[EXTRUDER_E0].move(ENDSTOP_FEED_LENGTH);
            //            } else if (digitalRead(PIN_Z_MIN) == 0) {
            //                extruders[EXTRUDER_E0].move(-ENDSTOP_FEED_LENGTH);
            //            }
            break;
            //
        case EXTRUDER_E1:
            //            if (digitalRead(PIN_Z_MAX) == 0) {
            //                extruders[EXTRUDER_E1].move(ENDSTOP_FEED_LENGTH);
            //            } else if (digitalRead(PIN_Z_MIN) == 0) {
            //                extruders[EXTRUDER_E1].move(-ENDSTOP_FEED_LENGTH);
            //            }
            break;
    }


}

void BtdeController::loadFromEeprom() {
    EEPROM.get(0, systemConfig);
    if (systemConfig.id != 0xAABBCCDD) {
        systemConfig.id = 0xAABBCCDD;
        systemConfig.currentExtruderName = EXTRUDER_X;
        systemConfig.filamentStatus[EXTRUDER_X] = UNLOADED;
        systemConfig.filamentStatus[EXTRUDER_Y] = UNLOADED;
        systemConfig.filamentStatus[EXTRUDER_Z] = UNLOADED;
        systemConfig.filamentStatus[EXTRUDER_E0] = UNLOADED;
        systemConfig.filamentStatus[EXTRUDER_E1] = UNLOADED;
        saveToEeprom();
        loadedFromEeprom = false;
    } else {
        loadedFromEeprom = true;
    }
}

void BtdeController::saveToEeprom() {
    EEPROM.put(0, systemConfig);
}

boolean BtdeController::isLoadedFromEeprom() {
    return this->loadedFromEeprom;
}

void BtdeController::initSystem() {
    loadFromEeprom();
    switch (this->systemConfig.currentExtruderName) {
        case EXTRUDER_X:
            extruders[EXTRUDER_X].enableMotor();
            break;
        case EXTRUDER_Y:
            extruders[EXTRUDER_Y].enableMotor();
            break;
        case EXTRUDER_Z:
            extruders[EXTRUDER_Z].enableMotor();
            break;
        case EXTRUDER_E0:
            extruders[EXTRUDER_E0].enableMotor();
            break;
        case EXTRUDER_E1:
            extruders[EXTRUDER_E1].enableMotor();
            break;
    }
}
