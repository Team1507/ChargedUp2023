#include "commands/CmdPouchIntakeDeploy.h"


CmdPouchIntakeDeploy::CmdPouchIntakeDeploy(Pouch *pouch) 
{
  m_pouch = pouch;
}

// Called when the command is initially scheduled.
void CmdPouchIntakeDeploy::Initialize() 
{
  m_pouch->DeployIntake();
}
