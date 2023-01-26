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
  std::cout<<"Pouch owo"<<std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdPouchDefault::Execute() {}

// Called once the command ends or is interrupted.
void CmdPouchDefault::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdPouchDefault::IsFinished() 
{
  return false;
}
