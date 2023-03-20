#include "commands/CmdTurretSetEncoder.h"
#include "subsystems/Arm.h"

CmdTurretSetEncoder::CmdTurretSetEncoder(Arm *arm, float encoder)
{
  m_arm = arm;
  m_encoder = encoder;
 
}

void CmdTurretSetEncoder::Initialize() 
{
  #ifdef TURRET
    m_arm->TurretSetEncoder(m_encoder);
  #endif
}
