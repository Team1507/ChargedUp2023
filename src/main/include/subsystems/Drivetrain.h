// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "subsystems/SwerveModule.h"
#include "AHRS.h"

#include "Constants.h"



class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();

  void Periodic() override;

  enum driveType { ROBOTCENTRIC, FIELDCENTRIC };
  void SetDriveType( driveType type );
  driveType GetDriveType( void );


  void RobotcentricDriveVelocity( float fwdrev, float rightleft, float rotate );
  void FieldcentricDriveVelocity( float fwdrev, float rightleft, float rotate );

  void RobotcentricDrive( float fwdrev, float rightleft, float rotate );
  void FieldcentricDrive( float fwdrev, float rightleft, float rotate );
  void Stop( void );

  void ForceSteerAngle( float angle );
  void ForcePark(void);
  
  float FalconTempGetAverage(void);

  //Encoders
  void HardResetDriveEncoders(void);
  void ResetDriveEncoders(void);
  void ResetSteerEncoders(void);

  //NavX
  bool   IsGyroConnected(void);
  double GetGyroYaw(void);            //yaw: Relative -180 to +180
  double GetGyroAngle(void);          //angle: absolute -inf to +inf
  double GetGyroRate(void);
  void   ZeroGyro(); 
  bool   IsGyroBusy(void);            //Busy Calibrating
  float  GetGyroPitch(void);
  float  GetGyroRoll(void);
  void   SetAngleOffset(float angle);

  //Odometry
  void   ResetOdometry(void);
  float  GetOdometryX(void);           //inches
  float  GetOdometryY(void);           //inches
  float  GetOdometryHeading(void);     //degrees

  //Absolute Encoder calibration
  void   CalibrateSteerEncoderAbsoutePositionStart(void);
  void   CalibrateSteerEncoderAbsoutePositionOffset(void);

 private:

  driveType m_driveType;  

  AHRS m_ahrs{frc::SPI::Port::kMXP};	    //NavX

  double m_angleAdjust;

  float m_falcAvg;

  //Module Odometry
  void  OdometryPeriodic(void);
  float m_curr_x;   //inches
  float m_curr_y;   //inches

  //Swerve Modules
  //    FL^FR
  //    RL RR
  SwerveModule m_frontRight{ FRONT_RIGHT_DRIVE_MOTOR_CAN_ID,  FRONT_RIGHT_STEER_MOTOR_CAN_ID,  FRONT_RIGHT_STEER_ENCODER_CAN_ID, "FR" };
  SwerveModule m_frontLeft { FRONT_LEFT_DRIVE_MOTOR_CAN_ID,   FRONT_LEFT_STEER_MOTOR_CAN_ID,   FRONT_LEFT_STEER_ENCODER_CAN_ID,  "FL" };
  SwerveModule m_rearLeft  { REAR_LEFT_DRIVE_MOTOR_CAN_ID,    REAR_LEFT_STEER_MOTOR_CAN_ID,    REAR_LEFT_STEER_ENCODER_CAN_ID,   "RL" };
  SwerveModule m_rearRight { REAR_RIGHT_DRIVE_MOTOR_CAN_ID,   REAR_RIGHT_STEER_MOTOR_CAN_ID,   REAR_RIGHT_STEER_ENCODER_CAN_ID,  "RR" };
 

  //Array of pointers to swerve modules, to make processing each module more convenient
  SwerveModule* m_moduleList[NUM_SWERVE_MODULES];


};
