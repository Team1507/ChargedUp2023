// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

class Pouch : public frc2::SubsystemBase {
 public:
  Pouch();
  enum Intake {Inner,Outer};
  void SetIntakePower(float power,Intake type);
  float ReadSensorState(void);
  void SetRampPosition(float position);
  void DeployIntake(Intake type);
  void RetractIntake(Intake type);
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
