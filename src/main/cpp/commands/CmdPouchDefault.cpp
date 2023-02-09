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
  
  if (m_pouch->IntakeGetCurrent() > INNER_INTAKE_CURRENT_LIMIT)
  {
     m_pouch->IntakeSetPower(0.00, Pouch::WhatIntake::Inner);
     m_pouch->IntakeEnable(false);
  }
  else if (IntakeEnabled) 
  {
    m_pouch->IntakeSetPower(INNER_INTAKE_POWER, Pouch::WhatIntake::Inner);
  }

}

// Called once the command ends or is interrupted.
void CmdPouchDefault::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdPouchDefault::IsFinished() 
{
  return false;
}
