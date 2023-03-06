#include "commands/CmdTurretTurn2Angle.h"
#include <math.h>
#include <iostream>

#define TOLORANCE 2.0

CmdTurretTurn2Angle::CmdTurretTurn2Angle(Arm *arm, double angle) 
{
  m_angle = angle;
  m_arm = arm;
}

void CmdTurretTurn2Angle::Initialize() 
{
  m_arm->TurretTurn2Angle(m_angle);
}

void CmdTurretTurn2Angle::Execute() {}

void CmdTurretTurn2Angle::End(bool interrupted) {}

bool CmdTurretTurn2Angle::IsFinished() 
{
  // std::cout<<((m_angle - m_arm->TurretGetAngle()))<<std::endl;
  if(fabs((m_angle - m_arm->TurretGetAngle())) < TOLORANCE )
  {
    return true;
  }
  else
  {
    return false;
  }
}
