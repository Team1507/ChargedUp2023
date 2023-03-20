#include "commands/CmdTurretSetPower.h"
#include "subsystems/Arm.h"

CmdTurretSetPower::CmdTurretSetPower(Arm *arm, float power)
{
  m_arm = arm;
  m_power = power;
}

void CmdTurretSetPower::Initialize() 
{
  #ifdef TURRET
  m_arm->TurretSetPower(m_power);
  #endif
}
