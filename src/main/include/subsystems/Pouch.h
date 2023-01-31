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

class Pouch : public frc2::SubsystemBase {
 public:
  Pouch();
  
  enum WhatIntake {Inner,Outer};
  void SetIntakePower(float power,WhatIntake type);
  bool ReadSensorState(void);
  void SetRampPosition(bool deploy);
  void DeployIntake(WhatIntake type);
  void RetractIntake(WhatIntake type);
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
    rev::CANSparkMax m_OuterLeft {CAN_ID_POUCH_OUTTER_LEFT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_OuterRight {CAN_ID_POUCH_OUTTER_RIGHT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_Inner {CAN_ID_POUCH_INNER, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    frc::DoubleSolenoid m_leftOuterIntake {PCM_CAN_ID, frc::PneumaticsModuleType::CTREPCM, LEFT_OUTER_INTAKE_DEPLOY_PCM, LEFT_OUTER_INTAKE_RETRACT_PCM};
    frc::DoubleSolenoid m_rightOuterIntake {PCM_CAN_ID, frc::PneumaticsModuleType::CTREPCM, RIGHT_OUTER_INTAKE_DEPLOY_PCM, RIGHT_OUTER_INTAKE_RETRACT_PCM};
    frc::DoubleSolenoid m_leftOuterIntakeClose {PCM_CAN_ID, frc::PneumaticsModuleType::CTREPCM, LEFT_OUTER_INTAKE_CLOSE_DEPLOY_PCM, LEFT_OUTER_INTAKE_CLOSE_RETRACT_PCM};
    frc::DoubleSolenoid m_rightOuterIntakeClose {PCM_CAN_ID, frc::PneumaticsModuleType::CTREPCM, RIGHT_OUTER_INTAKE_CLOSE_DEPLOY_PCM, RIGHT_OUTER_INTAKE_CLOSE_RETRACT_PCM};
        frc::DoubleSolenoid m_ramp {PCM_CAN_ID, frc::PneumaticsModuleType::CTREPCM, RAMP_DEPLOY_PCM, RAMP_RETRACT_PCM};





    frc::DigitalInput m_GamePieceDetect{GAME_PIECE_DETECT_ID};
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
