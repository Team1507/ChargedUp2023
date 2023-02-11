// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdPouchDefault.h"
#include "subsystems/Pouch.h"
#include <iostream>

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
}

// Called repeatedly when this Command is scheduled to run
void CmdPouchDefault::Execute() 
{
  bool IntakeEnabled = m_pouch->IntakeIsEnable();
  
  
  if (IntakeEnabled && !m_isIntaking) 
  {
    m_isIntaking = true;
    m_pouch->IntakeSetPower(INNER_INTAKE_POWER, Pouch::WhatIntake::Inner);
  }
  else if(!IntakeEnabled && m_isIntaking)
  {
    m_isIntaking = false;
    m_pouch->IntakeSetPower(0, Pouch::WhatIntake::Inner);
  }
  else if (m_pouch->IntakeGetCurrent() > INNER_INTAKE_CURRENT_LIMIT)
  {
    m_pouch->IntakeEnable(false);
  }
  else if (m_pouch->ReadSensorState())
  {
    m_pouch->IntakeEnable(false);
  }

}

// Called once the command ends or is interrupted.
void CmdPouchDefault::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdPouchDefault::IsFinished() 
{
  return false;
}
