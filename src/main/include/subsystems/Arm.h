// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "CTRE/Phoenix.h"
#include "rev/CANSparkMax.h"
#include "Constants.h"
#include <frc/DoubleSolenoid.h>
#include <frc/PneumaticsModuleType.h>

class Arm : public frc2::SubsystemBase 
{
 public:
  Arm();
  void Periodic() override;
  //**********************************Turret******************************
  void TurretSetAngle(float angle);
  void TurretSetPower(float power);
  void TurretSetEncoder(float encoder);
  
  float TurretGetPower(void);
  float TurretGetAngle(void);
  float TurretGetEncoder(void);
  //***********************************ARM*********************************
  void ElevationArmSetPosition(int position);
  void EleveationExtensionArm(int position);
  /**
  * Will be called periodically whenever the CommandScheduler runs.
   */

  // [:P] \\

 private:
   rev::CANSparkMax m_turret {CAN_ID_TURRET, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  frc::DoubleSolenoid  m_doublesolinoid {PCM_CAN_ID, frc::PneumaticsModuleType::CTREPCM, FRONT_INTAKE_DEPLOY_PCM, FRONT_INTAKE_RETRACT_PCM};
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  //TalonFX m_turret{CAN_TURRET_ID};
};