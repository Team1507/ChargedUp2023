#include "commands/CmdPouchIntakeRetract.h"

CmdPouchIntakeRetract::CmdPouchIntakeRetract(Pouch *pouch) 
{
  m_pouch = pouch;
}


void CmdPouchIntakeRetract::Initialize() 
{
  m_pouch->RetractIntake();
}
