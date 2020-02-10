/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BtdeController.h
 * Author: arsi
 *
 * Created on Sobota, 2020, februára 1, 22:38
 */

#ifndef BTDECONTROLLER_H
#define BTDECONTROLLER_H
#include "Extruder.h"
#include "config.h"
#include "EEPROM.h"

class BtdeController {
public:

    enum ExtrudersNames {
        EXTRUDER_X,
        EXTRUDER_Y,
        EXTRUDER_Z,
        EXTRUDER_E0,
        EXTRUDER_E1,
        EXTRUDER_END,
    };

    enum FilamentStatus {
        UNLOADED,
        IN_COMPENSATOR,
        IN_JOINER,
        LOADING,
        LOADED,
        WAIT_FOR_DIRECT
    };

    struct SystemConfig {
        FilamentStatus filamentStatus[5];
        ExtrudersNames currentExtruderName;
        uint32_t id;
    };

    BtdeController();
    Extruder getExtruder(ExtrudersNames ex);
    ExtrudersNames getCurrentExtruderName();
    void timerIsr();
    void endStopsIsr();
    void loadFromEeprom();
    void saveToEeprom();
    void resetEeprom();
    boolean isLoadedFromEeprom();
    void initSystem();
    void selectExtruderMotor(ExtrudersNames extruderName, boolean eeprom);
    void loadToCompensator(ExtrudersNames extruderName);
    void loadToJoiner(ExtrudersNames extruderName);
    void ejectFilament(ExtrudersNames extruderName);
    void toolChange(ExtrudersNames extruderName);
    
    
    FilamentStatus getFilamentStatus(ExtrudersNames extruderName);
    int getCompensatorToJoinerLength(ExtrudersNames extruderName);

private:
    SystemConfig systemConfig;
    boolean loadedFromEeprom = false;
    Extruder extruders[5] = {Extruder(STEPPER_X_STEP, STEPPER_X_DIR, STEPPER_X_ENABLE, ETRUDER_X_STEPS_PER_MM, ETRUDER_X_ACCELERATION, ETRUDER_X_MAX_SPEED, ETRUDER_X_REVERSE),
        Extruder(STEPPER_Y_STEP, STEPPER_Y_DIR, STEPPER_Y_ENABLE, ETRUDER_Y_STEPS_PER_MM, ETRUDER_Y_ACCELERATION, ETRUDER_Y_MAX_SPEED, ETRUDER_Y_REVERSE),
        Extruder(STEPPER_Z_STEP, STEPPER_Z_DIR, STEPPER_Z_ENABLE, ETRUDER_Z_STEPS_PER_MM, ETRUDER_Z_ACCELERATION, ETRUDER_Z_MAX_SPEED, ETRUDER_Z_REVERSE),
        Extruder(STEPPER_E0_STEP, STEPPER_E0_DIR, STEPPER_E0_ENABLE, ETRUDER_E0_STEPS_PER_MM, ETRUDER_E0_ACCELERATION, ETRUDER_E0_MAX_SPEED, ETRUDER_E0_REVERSE),
        Extruder(STEPPER_E1_STEP, STEPPER_E1_DIR, STEPPER_E1_ENABLE, ETRUDER_E1_STEPS_PER_MM, ETRUDER_E1_ACCELERATION, ETRUDER_E1_MAX_SPEED, ETRUDER_E1_REVERSE)};
};

#endif /* BTDECONTROLLER_H */

