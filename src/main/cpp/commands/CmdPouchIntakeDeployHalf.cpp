#include "commands/CmdPouchIntakeDeployHalf.h"


CmdPouchIntakeDeployHalf::CmdPouchIntakeDeployHalf(Pouch *pouch) 
{
  m_pouch = pouch;
}


void CmdPouchIntakeDeployHalf::Initialize() 
{
  m_pouch->IntakeDeployHalf();
}
