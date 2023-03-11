#include "commands/CmdPouchInnerIntakeRotate.h"

CmdPouchInnerIntakeRotate::CmdPouchInnerIntakeRotate(Pouch *pouch) 
{
  m_pouch = pouch;
  m_startingPosition = m_pouch->InnerIntakeGetEncoder();
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
