// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "rev/CANSparkMax.h"
#include "Constants.h"
#include <frc2/command/SubsystemBase.h>
#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>
#include <frc/PneumaticsModuleType.h>
#include "ctre/Phoenix.h"

class Pouch : public frc2::SubsystemBase {
 public:
  Pouch();
  
  enum WhatIntake {Inner,Outer};
  void SetIntakePower(float power,WhatIntake type);
  bool ReadSensorState(void);
  void SetRampPosition(bool deploy);
  void DeployIntake(void);
  void RetractIntake(void);
  void OpenOuterIntake(void);
  void CloseOuterIntake(void);
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
   WPI_VictorSPX m_outerLeft {CAN_POUCH_OUTER_LEFT_ID};
   WPI_VictorSPX m_outerRight {CAN_POUCH_OUTER_RIGHT_ID};
 
    
    rev::CANSparkMax m_inner {CAN_POUCH_INNER_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::SparkMaxRelativeEncoder m_innerEncoder = m_inner.GetEncoder();
    rev::SparkMaxPIDController   m_innerPIDController = m_inner.GetPIDController();

    frc::DoubleSolenoid m_leftOuterIntake {CAN_PCM_ID, frc::PneumaticsModuleType::CTREPCM, PCM_LEFT_OUTER_INTAKE_DEPLOY_ID, PCM_LEFT_OUTER_INTAKE_RETRACT_ID};
    frc::DoubleSolenoid m_rightOuterIntake {CAN_PCM_ID, frc::PneumaticsModuleType::CTREPCM, PCM_RIGHT_OUTER_INTAKE_DEPLOY_ID, PCM_RIGHT_OUTER_INTAKE_RETRACT_ID};
    frc::DoubleSolenoid m_leftOuterIntakeClose {CAN_PCM_ID, frc::PneumaticsModuleType::CTREPCM, PCM_LEFT_OUTER_INTAKE_CLOSE_DEPLOY_ID, PCM_LEFT_OUTER_INTAKE_CLOSE_RETRACT_ID};
    frc::DoubleSolenoid m_rightOuterIntakeClose {CAN_PCM_ID, frc::PneumaticsModuleType::CTREPCM, PCM_RIGHT_OUTER_INTAKE_CLOSE_DEPLOY_ID, PCM_RIGHT_OUTER_INTAKE_CLOSE_RETRACT_ID};
    
    frc::DoubleSolenoid m_ramp {CAN_PCM_ID, frc::PneumaticsModuleType::CTREPCM, PCM_RAMP_DEPLOY_ID, PCM_RAMP_RETRACT_ID};





    frc::DigitalInput m_gamePieceDetect{DIO_GAME_PIECE_DETECT_ID};
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
