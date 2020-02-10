/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   config.h
 * Author: arsi
 *
 * Created on Sobota, 2020, februára 1, 22:50
 */

#ifndef CONFIG_H
#define CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

    //-------------------------------------------------------------------------
#define ENDSTOP_FEED_LENGTH 10// Length of filament retracted/pushed on endstop hit
#define BOWDEN_EXTRUDER_TO_COMPENSATOR_TUBE_LENGTH 580 //PTFE tube length in mm 
#define FROM_DIRECT_TO_PARKING_LENGTH 90 //Length of compensator including quick connectors
#define COMPENSATOR_TO_JOINER_TUBE_LENGTH_X 985 // PTFE tube length in mm + mm to inactive filament position in joiner
#define COMPENSATOR_TO_JOINER_TUBE_LENGTH_Y 970 // PTFE tube length in mm + mm to inactive filament position in joiner
#define COMPENSATOR_TO_JOINER_TUBE_LENGTH_Z 970 // PTFE tube length in mm + mm to inactive filament position in joiner
#define COMPENSATOR_TO_JOINER_TUBE_LENGTH_E0 970 // PTFE tube length in mm + mm to inactive filament position in joiner
#define COMPENSATOR_TO_JOINER_TUBE_LENGTH_E1 970 // PTFE tube length in mm + mm to inactive filament position in joiner
#define JOINER_INACTIVE_POSITION_TO_DIRECT_EXTRUDER 25 // Length from inactive position in joiner to direct extruder in mm

    //--------------Extruders--------------------------------------------------
#define ETRUDER_X_STEPS_PER_MM 397
#define ETRUDER_X_ACCELERATION 500 // 20kHz/(acceleration*hardcoded curve)
#define ETRUDER_X_MAX_SPEED 0 // 0-20kHz, 1-10kHz, 2-5kHz ...
#define ETRUDER_X_REVERSE true

#define ETRUDER_Y_STEPS_PER_MM 397
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
    //
#define STEPPER_E1_STEP 36
    //
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


#ifdef __cplusplus
}
#endif

#endif /* CONFIG_H */

