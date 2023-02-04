#include "commands/CmdClawIntakeEnable.h"

CmdClawIntakeEnable::CmdClawIntakeEnable(Claw *claw, bool enable) 
{
  m_claw = claw;
  m_isEnabled = enable;
}


void CmdClawIntakeEnable::Initialize() 
{
  m_claw->ClawIntakeEnable(m_isEnabled);
}
