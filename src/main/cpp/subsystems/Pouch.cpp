// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Pouch.h"
#include <frc/smartdashboard/SmartDashboard.h>
Pouch::Pouch(frc::PowerDistribution *pdh) 
{
  m_isIntaking = false;
  m_inner.RestoreFactoryDefaults(); 
  m_inner.SetInverted(true);
  m_innerEncoder.SetPosition(0.0); 
  m_innerPIDController.SetP(0.05); // change later
  m_innerPIDController.SetI(0.0); // change later
  m_innerPIDController.SetD(0.0); // change later
  m_innerPIDController.SetSmartMotionAllowedClosedLoopError(0.3); // change later
  m_inner.SetOpenLoopRampRate(0.5); // change later
  m_pdh = pdh;
  // m_outerLeft.RestoreFactoryDefaults();
  m_outerLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
  // m_outerRight.RestoreFactoryDefaults();
  m_outerLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);

}
// Crocs
void Pouch::IntakeSetPower(float power,WhatIntake type)
{
  if(WhatIntake::Inner == type)
  {
    m_inner.Set(power);  
  } 
  else if (WhatIntake::Outer == type)
  {
    m_outerLeft.Set(power);
    m_outerRight.Set(-power);
  }
}
void Pouch::InnerIntakeSetPosition(float position)
{
  m_innerEncoder.SetPosition(position);  
}
void Pouch::InnerIntakeTurnToPosition(float position)
{
  // int wantedPosition = InnerIntakeGetEncoder() - (((int)InnerIntakeGetEncoder())%INNER_INTAKE_TICKS_TO_REV);
  // frc::SmartDashboard::PutNumber("Wanted Position",wantedPosition);
  // m_innerPIDController.SetReference(wantedPosition,rev::CANSparkMax::ControlType::kPosition);
}
// void Pouch::InnerIntakeTurnOnce(void) 
// {
//   // int wantedPosition = InnerIntakeGetEncoder() - (((int)InnerIntakeGetEncoder())%INNER_INTAKE_TICKS_TO_REV);

//   int currentPosition =  InnerIntakeGetEncoder();
//   int lastZero        =  currentPosition - ((int)currentPosition%INNER_INTAKE_TICKS_TO_REV);
  

//   frc::SmartDashboard::PutNumber("Wanted Position",wantedPosition);
//   m_innerPIDController.SetReference(wantedPosition,rev::CANSparkMax::ControlType::kPosition);
// }
int  Pouch::InnerIntakeGetEncoder(void)
{
  return m_innerEncoder.GetPosition();
}
double Pouch::IntakeGetCurrent(void)
{
  return m_pdh->GetCurrent(PDH_INNER_INTAKE_PORT);
}
void Pouch::IntakeDeploy(void)
{
  m_OuterIntake.Set(frc::DoubleSolenoid::kReverse);   
}

void Pouch::IntakeRetract(void)
{
  m_OuterIntake.Set(frc::DoubleSolenoid::kForward);
}

bool Pouch::IntakeIsDeployed(void)
{
  return m_OuterIntake.Get() == frc::DoubleSolenoid::kReverse;
}

void Pouch::SetRampPosition(bool deploy)
{
  if( deploy == true )
  {
    m_ramp.Set(frc::DoubleSolenoid::kForward);
  }
  if( deploy == false)
  {
    m_ramp.Set(frc::DoubleSolenoid::kReverse);
  }
}

bool Pouch::ReadSensorState(void)
{
  return m_gamePieceDetect.Get();
}


void Pouch::IntakeEnable(bool enable)
{
  m_isIntaking=enable;
}

bool Pouch::IntakeIsEnable(void)
{
  return m_isIntaking;
}
void Pouch::OuterIntakeClose()
{
  m_outerIntakeClose.Set(frc::DoubleSolenoid::kForward);
}
void Pouch::OuterIntakeOpen()
{
  m_outerIntakeClose.Set(frc::DoubleSolenoid::kReverse);
}

// This method will be called once per scheduler run
void Pouch::Periodic() 
{
  frc::SmartDashboard::PutBoolean("Pouch Gamepiece Detect", ReadSensorState());
  frc::SmartDashboard::PutNumber("Inner Intake Encoder",InnerIntakeGetEncoder());
}
