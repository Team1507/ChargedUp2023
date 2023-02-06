// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdClawDefault.h"
#include "subsystems/Claw.h"
#include <iostream>
#define CLAW_INTAKE_POWER 0.5


CmdClawDefault::CmdClawDefault(Claw *claw) 
{
  AddRequirements(claw); 
  m_claw = claw;
  m_isIntaking = false;
}

void CmdClawDefault::Initialize() 
{
 std::cout<<"Claw :3"<<std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdClawDefault::Execute() 
{
  if(m_claw->ClawIntakeGetEnable() && !m_isIntaking) 
  {
    m_claw->ClawSetPower(CLAW_INTAKE_POWER);
    m_isIntaking = true;
  }
  else if(!m_claw->ClawIntakeGetEnable() && m_isIntaking)
  {
    m_claw->ClawSetPower(0.0);
    m_isIntaking = false;
  }
}

// Called once the command ends or is interrupted.
void CmdClawDefault::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdClawDefault::IsFinished() 
{

  return false;
}
