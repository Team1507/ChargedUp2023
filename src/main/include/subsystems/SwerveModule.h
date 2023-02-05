// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Timer.h>

#include "ctre/Phoenix.h"

class SwerveModule : public frc2::SubsystemBase {
 public:
  SwerveModule(const int driveMotorCanID, const int steerMotorCanID, const int steerEncoderCanID, const std::string debugID);

  void Periodic() override;



  //Set Modes
  void SetSteerAngle( float angle );
  void SetSteerAngleV2( float angle );
  void SetDriveMotor( float power );
  void SetDriveVelocity( float speed );

  

  //Steer Encoders
  double GetSteerEncoderPosition(void);
  double GetSteerEncoderAbsoutePosition(void);
  double GetSteerMotorPosition(void);
  void   ResetSteerEncoders(void);

  //Drive Encoders
  int  GetDriveEncoder(void);
  void HardResetDriveEncoder(void);
  void SoftResetDriveEncoder(void);


  //Motor Status
  float  GetDriveMotor( void );
  float  GetSteerMotor( void );
  bool   GetDriveInvertion( void );
  float  GetFalconTemp(void);

  //Odometry
  void   ResetModuleOdometry(void);
  void   ModuleOdometryPeriodic(void);
  float  GetModuleOdometryX(void);           //inches
  float  GetModuleOdometryY(void);           //inches
  float  GetModuleOdometryDeltaX(void);      //inches
  float  GetModuleOdometryDeltaY(void);      //inches
  float  GetModuleOdometryVel(void);         //in/sec
  float  GetModuleOdometryHeading(void);     //degrees


  //Testing only!  
  void   SetSteerMotor( float power );  


  //Absolute Encoder calibration
  void   CalibrateSteerEncoderAbsoutePositionStart(void);
  void   CalibrateSteerEncoderAbsoutePositionOffset(void);
 
 

 
 private:

  TalonFX   m_driveMotor;
  TalonFX   m_steerMotor;
  CANCoder  m_steerEncoder;
  
  std::string   m_dbgID;
  frc::Timer    m_timer;

  float m_desired_steer_angle; 

  int   m_drive_encoder_zero;
  bool  m_invert_drive;       //invert drive direction



    //Module Odometry
    int   m_prev_drive_encoder;
    float m_prev_timestamp;

    float m_curr_x;   //inches
    float m_curr_y;   //inches
    float m_delta_x;  //inches
    float m_delta_y;  //inches
    float m_curr_v;   //inches/sec

};
