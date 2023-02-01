// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "rev/CANSparkMax.h"
#include "Constants.h"
#include <frc/DigitalInput.h>

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
  void  WristSetPower(float power);     //for Debug use Only 
  float WristGetPower(void);            //for Debug use Only 
  bool  ReadSensorState(void);         //Change Return Type Later


 private:
  rev::CANSparkMax m_claw {CAN_ID_CLAW, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_wrist {CAN_ID_WRIST, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  frc::DigitalInput m_ClawGamePiece {CLAW_GAME_PIECE_ID};

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  // Shoes

};
