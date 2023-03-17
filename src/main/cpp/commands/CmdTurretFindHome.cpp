#include "commands/CmdTurretFindHome.h"

CmdTurretFindHome::CmdTurretFindHome(Arm *arm) 
{
  m_arm = arm;
}


void CmdTurretFindHome::Initialize() 
{
  m_arm->TurretSetPower(.05);
}


void CmdTurretFindHome::Execute() 
{

}


void CmdTurretFindHome::End(bool interrupted) 
{
  m_arm->TurretTurn2Angle(0);
}


bool CmdTurretFindHome::IsFinished() 
{
  if(m_arm->TurretGetLeftLimitSW())
  {
    return true;
  }
  else return false;
}
