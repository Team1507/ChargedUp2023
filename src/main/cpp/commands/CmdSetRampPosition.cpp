
#include "commands/CmdSetRampPosition.h"
#include "subsystems/Pouch.h"
CmdSetRampPosition::CmdSetRampPosition(Pouch *pouch, bool position)
{
 m_pouch = pouch;
 m_position = position;
}

// Called when the command is initially scheduled.
void CmdSetRampPosition::Initialize()
{
  m_pouch->SetRampPosition(m_position);
}
