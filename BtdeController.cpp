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
    for (int i = 0; i < EXTRUDER_END; i++) {
        extruders[i].timer_isr();
    }
}

void BtdeController::endStopsIsr() {
    if (this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == LOADED
            || this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == WAIT_FOR_DIRECT) {
        //The filament is loaded into the direct extruder, turn on the pull / push algorithm
        switch (this->systemConfig.currentExtruderName) {
            case EXTRUDER_X:
                if (digitalRead(PIN_X_MAX) == 0 && this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == LOADED) {
                    extruders[EXTRUDER_X].move(-ENDSTOP_FEED_LENGTH);
                } else if (digitalRead(PIN_X_MIN) == 0) {
                    extruders[EXTRUDER_X].move(ENDSTOP_FEED_LENGTH);
                    if (this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == WAIT_FOR_DIRECT) {
                        this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] = LOADED;
                        saveToEeprom();
                    }
                }
                break;
            case EXTRUDER_Y:
                if (digitalRead(PIN_Y_MAX) == 0 && this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == LOADED) {
                    extruders[EXTRUDER_Y].move(-ENDSTOP_FEED_LENGTH);
                } else if (digitalRead(PIN_Y_MIN) == 0) {
                    extruders[EXTRUDER_Y].move(ENDSTOP_FEED_LENGTH);
                    if (this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == WAIT_FOR_DIRECT) {
                        this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] = LOADED;
                        saveToEeprom();
                    }
                }
                break;
            case EXTRUDER_Z:
                if (digitalRead(PIN_Z_MAX) == 0 && this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == LOADED) {
                    extruders[EXTRUDER_Z].move(-ENDSTOP_FEED_LENGTH);
                } else if (digitalRead(PIN_Z_MIN) == 0) {
                    extruders[EXTRUDER_Z].move(ENDSTOP_FEED_LENGTH);
                    if (this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == WAIT_FOR_DIRECT) {
                        this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] = LOADED;
                        saveToEeprom();
                    }
                }
                break;
            case EXTRUDER_E0:
                //            if (digitalRead(PIN_Z_MAX) == 0 && this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == LOADED) {
                //                extruders[EXTRUDER_E0].move(ENDSTOP_FEED_LENGTH);
                //            } else if (digitalRead(PIN_Z_MIN) == 0) {
                //                extruders[EXTRUDER_E0].move(-ENDSTOP_FEED_LENGTH);
//                if (this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == WAIT_FOR_DIRECT) {
//                    this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] = LOADED;
//                    saveToEeprom();
//                }
                //            }
                break;
                //
            case EXTRUDER_E1:
                //            if (digitalRead(PIN_Z_MAX) == 0 && this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == LOADED) {
                //                extruders[EXTRUDER_E1].move(ENDSTOP_FEED_LENGTH);
                //            } else if (digitalRead(PIN_Z_MIN) == 0) {
                //                extruders[EXTRUDER_E1].move(-ENDSTOP_FEED_LENGTH);
//                if (this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == WAIT_FOR_DIRECT) {
//                    this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] = LOADED;
//                    saveToEeprom();
//                }
                //            }
                break;
            case EXTRUDER_END:
                break;
        }
    } else if (this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == LOADING) {
        //handle endstop hint (filament is pressed into a direct extruder) and feed some filament to increase pressure
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

void BtdeController::resetEeprom() {
    systemConfig.id = 0xAABBCCDD;
    systemConfig.currentExtruderName = EXTRUDER_X;
    systemConfig.filamentStatus[EXTRUDER_X] = UNLOADED;
    systemConfig.filamentStatus[EXTRUDER_Y] = UNLOADED;
    systemConfig.filamentStatus[EXTRUDER_Z] = UNLOADED;
    systemConfig.filamentStatus[EXTRUDER_E0] = UNLOADED;
    systemConfig.filamentStatus[EXTRUDER_E1] = UNLOADED;
    saveToEeprom();
    loadedFromEeprom = false;
}

boolean BtdeController::isLoadedFromEeprom() {
    return this->loadedFromEeprom;
}

void BtdeController::initSystem() {
    loadFromEeprom();
    selectExtruderMotor(this->systemConfig.currentExtruderName, false);
}

void BtdeController::selectExtruderMotor(ExtrudersNames extruderName, boolean eeprom) {
    for (int i = 0; i < EXTRUDER_END; i++) {
        if (i == extruderName) {
            extruders[i].enableMotor();
        } else {
            extruders[i].didableMotor();
        }
    }
    systemConfig.currentExtruderName = extruderName;
    if (eeprom) {
        saveToEeprom();
    }

}

void BtdeController::loadToCompensator(ExtrudersNames extruderName) {
    if (getFilamentStatus(extruderName) == UNLOADED) {
        systemConfig.filamentStatus[extruderName] = LOADING;
        extruders[extruderName].enableMotor();
        extruders[extruderName].move(BOWDEN_EXTRUDER_TO_COMPENSATOR_TUBE_LENGTH);
        while (extruders[extruderName].getStatus() != Extruder::STOPPED) {
        }
        extruders[extruderName].didableMotor();
        systemConfig.filamentStatus[extruderName] = IN_COMPENSATOR;
        saveToEeprom();
    }
}

void BtdeController::loadToJoiner(ExtrudersNames extruderName) {
    if (getFilamentStatus(extruderName) == IN_COMPENSATOR) {
        systemConfig.filamentStatus[extruderName] = LOADING;
        extruders[extruderName].enableMotor();
        extruders[extruderName].move(getCompensatorToJoinerLength(extruderName)-FROM_DIRECT_TO_PARKING_LENGTH);
        while (extruders[extruderName].getStatus() != Extruder::STOPPED) {
        }
        extruders[extruderName].didableMotor();
        systemConfig.filamentStatus[extruderName] = IN_JOINER;
        saveToEeprom();
    }else if (getFilamentStatus(extruderName) == LOADED || getFilamentStatus(extruderName) == WAIT_FOR_DIRECT) {
        systemConfig.filamentStatus[extruderName] = LOADING;
        extruders[this->systemConfig.currentExtruderName].enableMotor();
        int length = FROM_DIRECT_TO_PARKING_LENGTH+10;
        extruders[extruderName].move(-length);
        while (extruders[extruderName].getStatus() != Extruder::STOPPED) {
        }
        extruders[extruderName].didableMotor();
        systemConfig.filamentStatus[extruderName] = IN_JOINER;
        saveToEeprom();
    }
}

void BtdeController::toolChange(ExtrudersNames extruderName) {
    if (getFilamentStatus(extruderName) == IN_JOINER) {
        if (this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == LOADED
                ||this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] == WAIT_FOR_DIRECT) {
            this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] = LOADING;
            extruders[this->systemConfig.currentExtruderName].enableMotor();
            extruders[this->systemConfig.currentExtruderName].move(-FROM_DIRECT_TO_PARKING_LENGTH);
            while (extruders[this->systemConfig.currentExtruderName].getStatus() != Extruder::STOPPED) {
            }
            extruders[this->systemConfig.currentExtruderName].didableMotor();
            this->systemConfig.filamentStatus[this->systemConfig.currentExtruderName] = IN_JOINER;
        }
        extruders[extruderName].enableMotor();
        systemConfig.filamentStatus[extruderName] = LOADING;
        extruders[extruderName].move(FROM_DIRECT_TO_PARKING_LENGTH+10);
        while (extruders[extruderName].getStatus() != Extruder::STOPPED) {
        }
        this->systemConfig.currentExtruderName = extruderName;
        systemConfig.filamentStatus[extruderName] = WAIT_FOR_DIRECT;
        saveToEeprom();
    }
}

void BtdeController::ejectFilament(ExtrudersNames extruderName) {
    if (getFilamentStatus(extruderName) != UNLOADED && getFilamentStatus(extruderName) != LOADING) {
        switch (getFilamentStatus(extruderName)) {
            case LOADED:
            {
                systemConfig.filamentStatus[extruderName] = LOADING;
                extruders[extruderName].enableMotor();
                int length = getCompensatorToJoinerLength(extruderName) + BOWDEN_EXTRUDER_TO_COMPENSATOR_TUBE_LENGTH + 50;
                extruders[extruderName].move(-length);
                while (extruders[extruderName].getStatus() != Extruder::STOPPED) {
                }
                extruders[extruderName].didableMotor();
                systemConfig.filamentStatus[extruderName] = UNLOADED;
                saveToEeprom();
            }
                break;
            case IN_JOINER:
            {
                systemConfig.filamentStatus[extruderName] = LOADING;
                extruders[extruderName].enableMotor();
                int length = getCompensatorToJoinerLength(extruderName) + BOWDEN_EXTRUDER_TO_COMPENSATOR_TUBE_LENGTH;
                extruders[extruderName].move(-length);
                while (extruders[extruderName].getStatus() != Extruder::STOPPED) {
                }
                extruders[extruderName].didableMotor();
                systemConfig.filamentStatus[extruderName] = UNLOADED;
                saveToEeprom();
            }
                break;
            case IN_COMPENSATOR:
            {
                systemConfig.filamentStatus[extruderName] = LOADING;
                extruders[extruderName].enableMotor();
                int length = BOWDEN_EXTRUDER_TO_COMPENSATOR_TUBE_LENGTH + 50;
                extruders[extruderName].move(-length);
                while (extruders[extruderName].getStatus() != Extruder::STOPPED) {
                }
                extruders[extruderName].didableMotor();
                systemConfig.filamentStatus[extruderName] = UNLOADED;
                saveToEeprom();
            }
                break;
        }
    }
}

BtdeController::FilamentStatus BtdeController::getFilamentStatus(ExtrudersNames extruderName) {
    return this->systemConfig.filamentStatus[extruderName];
}

int BtdeController::getCompensatorToJoinerLength(ExtrudersNames extruderName) {
    switch (extruderName) {
        case EXTRUDER_X:
            return COMPENSATOR_TO_JOINER_TUBE_LENGTH_X;
        case EXTRUDER_Y:
            return COMPENSATOR_TO_JOINER_TUBE_LENGTH_Y;
        case EXTRUDER_Z:
            return COMPENSATOR_TO_JOINER_TUBE_LENGTH_Z;
        case EXTRUDER_E0:
            return COMPENSATOR_TO_JOINER_TUBE_LENGTH_E0;
        case EXTRUDER_E1:
            return COMPENSATOR_TO_JOINER_TUBE_LENGTH_E1;
    }
}


