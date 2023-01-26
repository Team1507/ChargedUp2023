// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdClawDefault.h"
#include "subsystems/Claw.h"
#include <iostream>
CmdClawDefault::CmdClawDefault(Claw *claw) 
{
  AddRequirements(claw); 
  m_claw = claw;
}

void CmdClawDefault::Initialize() 
{
 std::cout<<"Claw :3"<<std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdClawDefault::Execute() {}

// Called once the command ends or is interrupted.
void CmdClawDefault::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdClawDefault::IsFinished() 
{

  return false;
}
