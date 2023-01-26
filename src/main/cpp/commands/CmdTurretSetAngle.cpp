#include "commands/CmdTurretSetAngle.h"


CmdTurretSetAngle::CmdTurretSetAngle(Arm *arm, float angle) 
{
  m_arm = arm;
  m_angle = angle;
}

// Called when the command is initially scheduled.
void CmdTurretSetAngle::Initialize() 
{
  m_arm->TurretSetAngle(m_angle);
}
