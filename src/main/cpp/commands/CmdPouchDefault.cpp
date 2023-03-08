// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdPouchDefault.h"
#include "subsystems/Pouch.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

CmdPouchDefault::CmdPouchDefault(Pouch *pouch)
{
  AddRequirements(pouch);
  m_pouch = pouch;
  m_isIntaking = false;
}

// Called when the command is initially scheduled.
void CmdPouchDefault::Initialize() 
{
  std::cout<<"Pouch"<<std::endl;
  m_sensorCount = 0;
}

// Called repeatedly when this Command is scheduled to run
void CmdPouchDefault::Execute() 
{
  bool IntakeEnabled = m_pouch->IntakeIsEnable();
  frc::SmartDashboard::PutNumber("Intake Current",m_pouch->IntakeGetCurrent());
  
  if (IntakeEnabled && !m_isIntaking) 
  {
    m_isIntaking = true;
    m_pouch->IntakeSetPower(INNER_INTAKE_POWER, Pouch::WhatIntake::Inner);
  }
  else if(!IntakeEnabled && m_isIntaking)
  {
    m_isIntaking = false;
    m_pouch->InnerIntakeTurnToPosition(0);
    m_pouch->SetRampPosition(false);
    m_pouch->IntakeSetPower(0.0, Pouch::WhatIntake::Outer);
  }
  else if (m_pouch->IntakeGetCurrent() > INNER_INTAKE_CURRENT_LIMIT && IntakeEnabled)
  {
    if(m_sensorCount > 3)
    {
      // std::cout<<"Ended by Current"<<std::endl;
      m_pouch->IntakeEnable(false);
      m_sensorCount=0;
    }
    else
    {
      // std::cout<<"Triped by Current"<<std::endl;
      m_sensorCount++;
    }
  }
  else if (m_pouch->ReadSensorState())
  {
    if(m_sensorCount > 3)
    {    
      // std::cout<<"Ended by sensor"<<std::endl;
      // m_pouch->IntakeEnable(false);
      m_pouch->SetRampPosition(false);
      m_sensorCount=0;
    }
    else
    {
      m_sensorCount++;
    }
  }
  else
  {
    // std::cout<<"Triped by sensor"<<std::endl;
    m_sensorCount=0;
  }

}

// Called once the command ends or is interrupted.
void CmdPouchDefault::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdPouchDefault::IsFinished() 
{
  return false;
}
