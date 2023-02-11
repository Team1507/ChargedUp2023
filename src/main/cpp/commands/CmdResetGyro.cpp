

#include "commands/CmdResetGyro.h"



CmdResetGyro::CmdResetGyro(Drivetrain *drivetrain) 
{
  m_drivetrain = drivetrain;
}


void CmdResetGyro::Initialize() 
{
  m_drivetrain->ZeroGyro();
}
