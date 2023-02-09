#include "commands/CmdIntakeSetEnable.h"


CmdIntakeSetEnable::CmdIntakeSetEnable(Pouch *pouch, bool enable) 
{
  m_pouch = pouch;
  m_enable = enable;
}

// Called when the command is initially scheduled.
void CmdIntakeSetEnable::Initialize() 
{
  m_pouch->IntakeEnable(m_enable);
}
