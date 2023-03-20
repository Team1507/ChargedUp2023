#include "commands/CmdPouchInnerIntakeRotate.h"

CmdPouchInnerIntakeRotate::CmdPouchInnerIntakeRotate(Pouch *pouch) 
{
  m_pouch = pouch;
  #ifdef INNER_INTAKE
  m_startingPosition = m_pouch->InnerIntakeGetEncoder();
  #endif
}

// Called when the command is initially scheduled.
void CmdPouchInnerIntakeRotate::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdPouchInnerIntakeRotate::Execute() {}

// Called once the command ends or is interrupted.
void CmdPouchInnerIntakeRotate::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdPouchInnerIntakeRotate::IsFinished() {
  return false;
}
