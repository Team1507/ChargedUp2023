// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

class Claw : public frc2::SubsystemBase {
 public:
  Claw();
  void ClawSetPower(float power);
  void WristSetPosition(float position);
  float ClawGetCurrent(void);
  float WristGetPosition(void);
  float ClawGetPower(void);
  void SensorReadState(void); //Change Return Type Later
  
  
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
