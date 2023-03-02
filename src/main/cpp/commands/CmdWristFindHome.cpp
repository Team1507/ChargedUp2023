#include "commands/CmdWristFindHome.h"

CmdWristFindHome::CmdWristFindHome(Claw *claw) 
{
  m_claw = claw;
}

void CmdWristFindHome::Initialize() 
{
  m_claw->WristSetPower(-.2);
}

void CmdWristFindHome::Execute() 
{

}

void CmdWristFindHome::End(bool interrupted) 
{

}

bool CmdWristFindHome::IsFinished() 
{
  if(m_claw->WristLimitTop())
  {
    return true;
  }
  else return false;
}
