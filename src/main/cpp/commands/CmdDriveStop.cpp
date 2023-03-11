
#include "commands/CmdDriveStop.h"


CmdDriveStop::CmdDriveStop(Drivetrain *drivetrain) 
{
  m_drivetrain = drivetrain;
}

// Called when the command is initially scheduled.
void CmdDriveStop::Initialize() 
{
  m_drivetrain->Stop();
}
