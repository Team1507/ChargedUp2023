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

enum ArmLevel{Level_Pouch, Low, Mid, High};
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
  void ElevationArmSetPosition(ArmLevel position);
  void ExtensionSetPosition(bool position);
  /**
  * Will be called periodically whenever the CommandScheduler runs.
   */

  // [:P] \\

 private:
  rev::CANSparkMax m_turret {CAN_ID_TURRET, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  frc::DoubleSolenoid  m_lowerArm {PCM_CAN_ID, frc::PneumaticsModuleType::CTREPCM, LOWER_ARM_DEPLOY_PCM, LOWER_ARM_RETRACT_PCM};
  frc::DoubleSolenoid m_upperArm {PCM_CAN_ID, frc::PneumaticsModuleType::CTREPCM, UPPER_ARM_DEPLOY_PCM, UPPER_ARM_RETRACT_PCM};
  frc::DoubleSolenoid m_armExtension {PCM_CAN_ID, frc::PneumaticsModuleType::CTREPCM, ARM_EXTENSION_DEPLOY_PCM, ARM_EXTENSION_RETRACT_PCM};

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  //TalonFX m_turret{CAN_TURRET_ID};
};