// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdClawDefault.h"
#include "subsystems/Claw.h"
#include <iostream>
#define CLAW_STALL_CURRENT 5 //To Be changed


CmdClawDefault::CmdClawDefault(Claw *claw) 
{
  AddRequirements(claw); 
  m_claw = claw;
  m_isIntaking = false;
}

void CmdClawDefault::Initialize() 
{
 std::cout<<"Claw Default Init"<<std::endl;
 m_delay = 10; // To Be Changed
}

// Called repeatedly when this Command is scheduled to run
void CmdClawDefault::Execute() 
{
  if(m_claw->ClawIntakeGetEnable() && !m_isIntaking && !m_claw->ReadSensorState()) 
  {
    m_claw->ClawSetPower(m_claw->ClawGetIntakePower());
    m_isIntaking = true;
    m_delay = 10;
    //std::cout<<"Claw Intake Power"<<m_claw->ClawGetIntakePower()<<std::endl;
  }
  else if(!m_claw->ClawIntakeGetEnable() && m_isIntaking)
  {
    m_claw->ClawSetPower(0.0);
    m_isIntaking = false;
    //std::cout<<"Claw A"<<std::endl;
  }
  else if(m_claw->ClawGetCurrent() > CLAW_STALL_CURRENT)
  {
    m_claw->ClawIntakeEnable(false);
    //std::cout<<"Claw B"<<std::endl;
  }
  else if(m_claw->ReadSensorState() && m_delay > 0)
  {
    m_delay--;
    if(m_delay <= 0)
    {
      m_claw->ClawSetPower(0.04);
      m_isIntaking = false;
      //std::cout<<"Claw C"<<std::endl;
    }
  }
}

// Called once the command ends or is interrupted.
void CmdClawDefault::End(bool interrupted) 
{
  std::cout<<"Claw Default End"<<std::endl;
}

// Returns true when the command should end.
bool CmdClawDefault::IsFinished() 
{

  return false;
}
