// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "rev/CANSparkMax.h"
#include "Constants.h"
#include <frc/DigitalInput.h> 
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/PowerDistribution.h>

#define CLAW_EJECT_POWER 0.0 //!!! CHANGE LATER !!!


#define CONE_INTAKE_POWER .6
#define CUBE_INTAKE_POWER .3

class Claw : public frc2::SubsystemBase {
 public:
  Claw(frc::PowerDistribution *pdh);
  /**
  * Will be called periodically whenever the CommandScheduler runs.
  */
  void Periodic() override;

  //************************************CLAW******************************************
  void  ClawSetPower(float power);
  float ClawGetPower(void);
  float ClawGetCurrent(void);
  void ClawIntakeEnable(bool enable);
  bool ClawIntakeGetEnable(void);
  void ClawSetIntakePower(float power);
  float ClawGetIntakePower(void);

  void ClawSetOuttakePower(float power);
  float ClawGetOuttakePower(void);


  //***********************************Wrist*******************************************
  void  WristSetPosition(float position);
  float WristGetPosition(void);
  float WristGetCurrent(void);
  void  WristSetPower(float power);     //for Debug use Only 
  float WristGetPower(void);            //for Debug use Only 
  bool  ReadSensorState(void);         //Change Return Type Later
  // bool  WristLimitSwitchForward(void);
  // bool  WristLimitSwitchReverse(void);
  bool  WristLimitTop(void);


 private:
  rev::CANSparkMax m_claw {CAN_CLAW_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_wrist {CAN_WRIST_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::SparkMaxRelativeEncoder m_wristEncoder = m_wrist.GetEncoder();
  rev::SparkMaxPIDController m_wristPID = m_wrist.GetPIDController();
  rev::SparkMaxLimitSwitch m_wristFWDLimit = m_wrist.GetForwardLimitSwitch(rev::SparkMaxLimitSwitch::Type::kNormallyOpen);
  rev::SparkMaxLimitSwitch m_wristREVLimit = m_wrist.GetReverseLimitSwitch(rev::SparkMaxLimitSwitch::Type::kNormallyOpen);
  frc::DigitalInput m_clawGamePiece {DIO_CLAW_DETECT_ID};
  bool m_intakeEnabled;
  frc::PowerDistribution *m_pdh;

  float m_clawIntakePower;
  float m_clawOuttakePower;

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  // Socks

};
