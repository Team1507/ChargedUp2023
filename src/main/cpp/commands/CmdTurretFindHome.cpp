#include "commands/CmdTurretFindHome.h"

CmdTurretFindHome::CmdTurretFindHome(Arm *arm) 
{
  m_arm = arm;
}


void CmdTurretFindHome::Initialize() 
{
  m_arm->TurretSetPower(.2);
}


void CmdTurretFindHome::Execute() 
{

}


void CmdTurretFindHome::End(bool interrupted) 
{

}


bool CmdTurretFindHome::IsFinished() 
{
  if(m_arm->TurretGetLeftLimitSW())
  {
    return true;
  }
  else return false;
}
