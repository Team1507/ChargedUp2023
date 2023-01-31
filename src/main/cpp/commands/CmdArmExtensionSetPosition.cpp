#include "commands/CmdArmExtensionSetPosition.h"

CmdArmExtensionSetPosition::CmdArmExtensionSetPosition(Arm *arm, bool extension) 
{
  m_arm = arm;
  m_isExtension = extension;
}

void CmdArmExtensionSetPosition::Initialize() 
{

}
