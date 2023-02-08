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
  void IntakeSetPower(float power,WhatIntake type);
  void IntakeEnable(bool enable);
  bool IntakeIsEnable(void);

  void IntakeDeploy(void);
  void IntakeRetract(void);

  void SetRampPosition(bool deploy);
  bool ReadSensorState(void);

  void Periodic() override;

 private:
  WPI_VictorSPX m_outerLeft {CAN_POUCH_OUTER_LEFT_ID};
  WPI_VictorSPX m_outerRight {CAN_POUCH_OUTER_RIGHT_ID};
    
  rev::CANSparkMax m_inner {CAN_POUCH_INNER_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::SparkMaxRelativeEncoder m_innerEncoder = m_inner.GetEncoder();
  rev::SparkMaxPIDController   m_innerPIDController = m_inner.GetPIDController();

  frc::DoubleSolenoid m_OuterIntake {CAN_PCM1_ID, frc::PneumaticsModuleType::CTREPCM, PCM_OUTER_INTAKE_DEPLOY_ID, PCM_OUTER_INTAKE_RETRACT_ID};
  frc::DoubleSolenoid m_ramp        {CAN_PCM1_ID, frc::PneumaticsModuleType::CTREPCM, PCM_RAMP_DEPLOY_ID, PCM_RAMP_RETRACT_ID};

  frc::DigitalInput m_gamePieceDetect{DIO_POUCH_DETECT_ID};

  bool m_isIntaking;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
