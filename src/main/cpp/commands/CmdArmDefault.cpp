// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdArmDefault.h"
#include "subsystems/Arm.h"
#include <iostream>
CmdArmDefault::CmdArmDefault(Arm *arm)
{
   AddRequirements(arm);
   m_arm = arm;
}

// Called when the command is initially scheduled.
void CmdArmDefault::Initialize() 
{
  std::cout<<"Arm Default Init"<<std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdArmDefault::Execute() 
{
  if (m_arm->TurretGetLeftLimitSW())
  {
    m_arm->TurretSetEncoder(0);
  }
}

// Called once the command ends or is interrupted.
void CmdArmDefault::End(bool interrupted) 
{
  std::cout<<"Arm Default End"<<std::endl;
}

// Returns true when the command should end.
bool CmdArmDefault::IsFinished() 
{
  return false;
}
