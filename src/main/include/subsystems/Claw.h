// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

class Claw : public frc2::SubsystemBase {
 public:
  Claw();
  /**
  * Will be called periodically whenever the CommandScheduler runs.
  */
  void Periodic() override;

  //************************************CLAW******************************************
  void  ClawSetPower(float power);
  float ClawGetPower(void);
  float ClawGetCurrent(void);

  //***********************************Wrist*******************************************
  void  WristSetPosition(float position);
  float WristGetPosition(void);

  void SensorReadState(void); //Change Return Type Later

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
