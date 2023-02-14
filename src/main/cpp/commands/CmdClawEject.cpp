#include "commands/CmdClawEject.h"

CmdClawEject::CmdClawEject(Claw *claw) 
{
  m_claw = claw;
}

void CmdClawEject::Initialize() 
{
  m_delay = 30;
}

void CmdClawEject::Execute() 
{
  if(m_delay > 0)
  {
    m_claw->ClawSetPower(m_claw->ClawGetOuttakePower());
    m_delay--;
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
