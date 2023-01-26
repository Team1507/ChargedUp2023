
#include "commands/CmdClawSetPower.h"
#include "subsystems/Claw.h"
CmdClawSetPower::CmdClawSetPower(Claw *claw, float power) 
{
 m_claw = claw;
 m_power = power;
}

void CmdClawSetPower::Initialize() 
{
  m_claw->ClawSetPower(m_power);
}
