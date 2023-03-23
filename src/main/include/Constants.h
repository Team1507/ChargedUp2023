// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

//********** DRIVETRAIN CONSTANTS **********
#define NUM_SWERVE_MODULES  4
//------------------------------------------
#define FRONT_LEFT_DRIVE_MOTOR_CAN_ID      1
#define FRONT_LEFT_STEER_MOTOR_CAN_ID      2
#define FRONT_LEFT_STEER_ENCODER_CAN_ID    3
//------------------------------------------
#define FRONT_RIGHT_DRIVE_MOTOR_CAN_ID     4
#define FRONT_RIGHT_STEER_MOTOR_CAN_ID     5
#define FRONT_RIGHT_STEER_ENCODER_CAN_ID   6
//------------------------------------------
#define REAR_LEFT_DRIVE_MOTOR_CAN_ID       7
#define REAR_LEFT_STEER_MOTOR_CAN_ID       8
#define REAR_LEFT_STEER_ENCODER_CAN_ID     9
//------------------------------------------
#define REAR_RIGHT_DRIVE_MOTOR_CAN_ID      10
#define REAR_RIGHT_STEER_MOTOR_CAN_ID      11
#define REAR_RIGHT_STEER_ENCODER_CAN_ID    12
//------------------------------------------



//********** CAN ID **********
#define CAN_TURRET_ID             13
#define CAN_CLAW_ID               14    //Gripper
#define CAN_WRIST_ID              15

#define CAN_POUCH_OUTER_LEFT_ID   16    //Left Collector
#define CAN_POUCH_OUTER_RIGHT_ID  17    //Right Collector
#define CAN_LED_UNDERGLOW         18    //LED Canifier
#define CAN_LED_DRIVER         18    //LED Canifier


#define CAN_PCM1_ID               19    //Belly Pan
#define CAN_PCM2_ID               20    //Mast
#define CAN_PDH_ID                21

#define CAN_POUCH_INNER_ID        22    //?


//********** PCM 1 Ports **********
#define PCM_RAMP_DEPLOY_ID               0
#define PCM_RAMP_RETRACT_ID              1
#define PCM_OUTER_INTAKE_DEPLOY_ID       2
#define PCM_OUTER_INTAKE_RETRACT_ID      3
#define PCM_OUTER_INTAKE_CLOSE_ID        4
#define PCM_OUTER_INTAKE_OPEN_ID         5
#define PCM_OUTER_INTAKE_HALF_EXTEND_ID  6
#define PCM_OUTER_INTAKE_HALF_RETRACT_ID 6

//********** PCM 2 Ports **********
#define PCM_ARM_EXTENSION_EXTEND_ID     0
#define PCM_ARM_EXTENSION_RETRACT_ID    1
#define PCM_LOWER_ARM_EXTEND_ID         2
#define PCM_LOWER_ARM_RETRACT_ID        3
#define PCM_UPPER_ARM_EXTEND_ID         4
#define PCM_UPPER_ARM_RETRACT_ID        5
#define PCM_AIR_SPRING_EXTEND_ID        6
#define PCM_AIR_SPRING_RETRACT_ID       7

//********** DIO Ports **********
#define DIO_CLAW_DETECT_ID                  1   //Cube
//      DIO_CLAW_DETECT_ID                  1   //Cone?
#define DIO_POUCH_DETECT_ID                 2
#define DIO_ELEVATION_HOME_LIMIT_SWITCH_ID  3


//********** PDH Ports **********
#define PDH_CLAW_PORT            5      //Gripper
#define PDH_WRIST_PORT           6
#define PDH_INNER_INTAKE_PORT    9      
namespace OperatorConstants 
{

constexpr int kDriverControllerPort = 0;



}  // namespace OperatorConstants
