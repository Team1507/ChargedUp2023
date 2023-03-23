#include "commands/CmdPouchIntakeRetractHalf.h"
CmdPouchIntakeRetractHalf::CmdPouchIntakeRetractHalf(Pouch *pouch) 
{
  m_pouch = pouch;
}


void CmdPouchIntakeRetractHalf::Initialize() 
{
  m_pouch->IntakeRetractHalf();
}
