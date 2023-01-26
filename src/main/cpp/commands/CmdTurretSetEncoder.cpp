
#include "commands/CmdTurretSetEncoder.h"
#include "subsystems/Arm.h"

CmdTurretSetEncoder::CmdTurretSetEncoder(Arm *arm, float encoder)
{
  m_arm = arm;
  m_encoder = encoder;
 
}

void CmdTurretSetEncoder::Initialize() 
{
 m_arm->TurretSetEncoder(m_encoder);
}
