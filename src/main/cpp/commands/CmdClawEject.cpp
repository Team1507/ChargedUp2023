#include "commands/CmdClawEject.h"
#include <iostream>

CmdClawEject::CmdClawEject(Claw *claw) 
{
  //AddRequirements(claw); 
  m_claw = claw;
}

void CmdClawEject::Initialize() 
{
  m_delay = 30; 
  m_claw->ClawSetPower(m_claw->ClawGetOuttakePower());
  std::cout<<"Claw Eject Init "<<m_claw->ClawGetOuttakePower()<<std::endl;
}

void CmdClawEject::Execute() 
{
  if(m_delay > 0)
  {
    m_delay--;
    std::cout<<m_delay<<std::endl;
  }
  else
  {
    m_claw->ClawSetPower(0);
  }
}

void CmdClawEject::End(bool interrupted) {}

bool CmdClawEject::IsFinished() 
{
  if(m_delay <= 0)
  {
    m_claw->ClawSetPower(0);
    return true;
  }
  else
  {
    return false;
  }
  
}
