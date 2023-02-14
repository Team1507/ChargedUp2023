#include "commands/CmdClawSetOuttakePower.h"

CmdClawSetOuttakePower::CmdClawSetOuttakePower(Claw *claw,double power) 
{
 m_claw = claw;
 m_power = power;
}

void CmdClawSetOuttakePower::Initialize() 
{
  m_claw->ClawSetOuttakePower(m_power);
  
}
