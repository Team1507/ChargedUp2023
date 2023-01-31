// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Pouch.h"

Pouch::Pouch() = default;

void Pouch::SetIntakePower(float power,WhatIntake type)
{
    if(WhatIntake::Inner == type)
    {
      m_Inner.Set(power);  
    } 
    else if (WhatIntake::Outer == type)
    {
      m_OuterLeft.Set(power);
      m_OuterRight.Set(power);
    }
}
bool Pouch::ReadSensorState(void)
{
    return m_GamePieceDetect.Get();
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
void Pouch::DeployIntake(WhatIntake type)
{
   if(WhatIntake::Inner == type)
    {
        
    } 
    else if (WhatIntake::Outer == type)
    {
      m_leftOuterIntake.Set(frc::DoubleSolenoid::kForward);
      m_rightOuterIntake.Set(frc::DoubleSolenoid::kForward);
    }
}
void Pouch::RetractIntake(WhatIntake type)
{
    if(WhatIntake::Inner == type)
    {
        
    } 
    else if (WhatIntake::Outer == type)
    {
      m_leftOuterIntake.Set(frc::DoubleSolenoid::kReverse);
      m_rightOuterIntake.Set(frc::DoubleSolenoid::kReverse);
    }
}
void Pouch::OpenOuterIntake(void)
{
  m_leftOuterIntakeClose.Set(frc::DoubleSolenoid::kReverse);
  m_rightOuterIntakeClose.Set(frc::DoubleSolenoid::kReverse);
}
void Pouch::CloseOuterIntake(void)
{
  m_leftOuterIntakeClose.Set(frc::DoubleSolenoid::kForward);
  m_rightOuterIntakeClose.Set(frc::DoubleSolenoid::kForward);
}
// This method will be called once per scheduler run
void Pouch::Periodic() {}
