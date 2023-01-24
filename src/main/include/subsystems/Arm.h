// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

class Arm : public frc2::SubsystemBase 
{
 public:
  Arm();
  void TurretSetAngle(float angle);
  void TurretSetPower(float power);
  void TurretSetEncoder(float encoder);
  float TurretGetPower(void);
  float TurretGetAngle(void);
  float TurretGetEncoder(void);
  void ElevationArmSetPosition(int position);
  void EleveationExtensionArm(int position);
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
