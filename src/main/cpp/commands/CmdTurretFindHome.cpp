#include "commands/CmdTurretFindHome.h"

CmdTurretFindHome::CmdTurretFindHome(Arm *arm) 
{
  m_arm = arm;
}


void CmdTurretFindHome::Initialize() 
{
  #ifdef TURRET
    m_arm->TurretSetPower(.05);
  #endif
}


void CmdTurretFindHome::Execute() 
{

}


void CmdTurretFindHome::End(bool interrupted) 
{
  #ifdef TURRET
  m_arm->TurretTurn2Angle(0);
  #endif
}


bool CmdTurretFindHome::IsFinished() 
{
  #ifdef TURRET
  if(m_arm->TurretGetLeftLimitSW())
  {
    return true;
  }
  else return false;
  #endif
  #ifndef TURRET
    return true;
  #endif
}
