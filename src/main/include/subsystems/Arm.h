// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "CTRE/Phoenix.h"
#include "Constants.h"
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
  void ElevationArmSetPosition(int position);
  void EleveationExtensionArm(int position);
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  //TalonFX m_turret{CAN_TURRET_ID};
};
