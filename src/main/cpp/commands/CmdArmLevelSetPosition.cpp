#include "commands/CmdArmLevelSetPosition.h"

CmdArmLevelSetPosition::CmdArmLevelSetPosition(Arm *arm, ArmLevel armLevel,Pouch *pouch, Claw *claw)
{
  m_pouch = pouch;
  m_arm = arm;
  m_armLevel = armLevel;
  m_claw = claw;
}

// Called when the command is initially scheduled.
void CmdArmLevelSetPosition::Initialize() 
{
  m_claw->WristHoldPosition(2);
  if(m_arm->ElevationArmGetPosition() == ArmLevel::Level_Pouch && m_pouch->IntakeIsDeployedHalf() && m_armLevel != ArmLevel::Level_Pouch)
  {
    m_pouch->IntakeDeployHalf();
  }
  else if(m_arm->ElevationArmGetPosition() != ArmLevel::Level_Pouch && m_pouch->IntakeIsDeployedHalf() && m_armLevel == ArmLevel::Level_Pouch)
  {
    m_pouch->IntakeDeployHalf();
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
