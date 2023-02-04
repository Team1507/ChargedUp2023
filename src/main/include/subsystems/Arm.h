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


 private:
  rev::CANSparkMax m_turret {CAN_TURRET_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::SparkMaxRelativeEncoder m_turretEncoder = m_turret.GetEncoder();

  rev::SparkMaxPIDController *m_turretPID;
  rev::SparkMaxLimitSwitch *m_turretFWDLimit;
  rev::SparkMaxLimitSwitch *m_turretREVLimit;
  frc::DoubleSolenoid  m_lowerArm {CAN_PCM_ID, frc::PneumaticsModuleType::CTREPCM, PCM_LOWER_ARM_DEPLOY_ID, PCM_LOWER_ARM_RETRACT_ID};
  frc::DoubleSolenoid m_upperArm {CAN_PCM_ID, frc::PneumaticsModuleType::CTREPCM, PCM_UPPER_ARM_DEPLOY_ID, PCM_UPPER_ARM_RETRACT_ID};
  frc::DoubleSolenoid m_armExtension {CAN_PCM_ID, frc::PneumaticsModuleType::CTREPCM, PCM_ARM_EXTENSION_DEPLOY_ID, PCM_ARM_EXTENSION_RETRACT_ID};

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  //TalonFX m_turret{CAN_TURRET_ID};
};