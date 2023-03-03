#include "commands/CmdArmLevelSetPosition.h"

CmdArmLevelSetPosition::CmdArmLevelSetPosition(Arm *arm, ArmLevel armLevel,Pouch *pouch)
{
  m_pouch = pouch;
  m_arm = arm;
  m_armLevel = armLevel;
}

// Called when the command is initially scheduled.
void CmdArmLevelSetPosition::Initialize() 
{
  if(m_arm->ElevationArmGetPosition() == ArmLevel::Level_Pouch && m_pouch->IntakeIsDeployed() && m_armLevel != ArmLevel::Level_Pouch)
  {
    m_pouch->IntakeDeploy();
  }
  else if(m_arm->ElevationArmGetPosition() != ArmLevel::Level_Pouch && m_pouch->IntakeIsDeployed() && m_armLevel == ArmLevel::Level_Pouch)
  {
    m_pouch->IntakeDeploy();
  }
  m_delay = 0;
  m_arm->ElevationArmSetPosition(m_armLevel);
}

// Called repeatedly when this Command is scheduled to run
void CmdArmLevelSetPosition::Execute() 
{
  // m_delay++;
  // if(m_delay >=OUTER_INTAKE_RETRACT_DELAY)
  // {
  //   m_pouch->IntakeRetract();
  // }
}

// Called once the command ends or is interrupted.
void CmdArmLevelSetPosition::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdArmLevelSetPosition::IsFinished() 
{  
  // if(!m_pouch->IntakeIsDeployed())
  // {
    return true;
 // }
  //return false;
}
