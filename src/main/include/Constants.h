// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

//********** DRIVETRAIN CONSTANTS **********
#define NUM_SWERVE_MODULES  4
//------------------------------------------
#define FRONT_RIGHT_DRIVE_MOTOR_CAN_ID     7
#define FRONT_RIGHT_STEER_MOTOR_CAN_ID     8
#define FRONT_RIGHT_STEER_ENCODER_CAN_ID   11
//------------------------------------------
#define FRONT_LEFT_DRIVE_MOTOR_CAN_ID      1
#define FRONT_LEFT_STEER_MOTOR_CAN_ID      2
#define FRONT_LEFT_STEER_ENCODER_CAN_ID    13
//------------------------------------------
#define REAR_LEFT_DRIVE_MOTOR_CAN_ID       3
#define REAR_LEFT_STEER_MOTOR_CAN_ID       4
#define REAR_LEFT_STEER_ENCODER_CAN_ID     14
//------------------------------------------
#define REAR_RIGHT_DRIVE_MOTOR_CAN_ID      5
#define REAR_RIGHT_STEER_MOTOR_CAN_ID      6
#define REAR_RIGHT_STEER_ENCODER_CAN_ID    12
//------------------------------------------







#define CAN_LED_UNDERGLOW 10
#define CAN_TURRET_ID 3
#define CAN_CLAW_ID 2
#define CAN_WRIST_ID 321
#define CAN_POUCH_OUTER_LEFT_ID 7
#define CAN_POUCH_OUTER_RIGHT_ID 5
#define CAN_POUCH_INNER_ID 12312
#define CAN_EXTEND_ID 123
#define CAN_RETRACT_ID 231
#define CAN_PCM_ID 12356
#define CAN_PDH_ID 10

#define PDH_CLAW_PORT 10
#define PDH_WRIST_PORT 10


#define PCM_LOWER_ARM_DEPLOY_ID 3211
#define PCM_LOWER_ARM_RETRACT_ID 12332
#define PCM_UPPER_ARM_DEPLOY_ID 1486
#define PCM_UPPER_ARM_RETRACT_ID 19575
#define PCM_ARM_EXTENSION_DEPLOY_ID 175895
#define PCM_ARM_EXTENSION_RETRACT_ID 1794
#define PCM_LEFT_OUTER_INTAKE_DEPLOY_ID 8465
#define PCM_LEFT_OUTER_INTAKE_RETRACT_ID 9385
#define PCM_RIGHT_OUTER_INTAKE_DEPLOY_ID 1752
#define PCM_RIGHT_OUTER_INTAKE_RETRACT_ID 3763
#define PCM_LEFT_OUTER_INTAKE_CLOSE_DEPLOY_ID 3285
#define PCM_LEFT_OUTER_INTAKE_CLOSE_RETRACT_ID 9632
#define PCM_RIGHT_OUTER_INTAKE_CLOSE_DEPLOY_ID 83906
#define PCM_RIGHT_OUTER_INTAKE_CLOSE_RETRACT_ID 295632
#define PCM_RAMP_DEPLOY_ID 104724
#define PCM_RAMP_RETRACT_ID 928532


#define DIO_CLAW_GAME_PIECE_ID 4
#define DIO_GAME_PIECE_DETECT_ID 47
#define DIO_ELEVATION_HOME_LIMIT_SWITCH_ID 129549


namespace OperatorConstants 
{

constexpr int kDriverControllerPort = 0;



}  // namespace OperatorConstants
