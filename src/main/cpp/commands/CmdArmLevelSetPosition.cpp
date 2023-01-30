#include "commands/CmdArmLevelSetPosition.h"
#include "subsystems/Arm.h"

CmdArmLevelSetPosition::CmdArmLevelSetPosition(Arm *arm, ArmLevel armLevel) 
{
    m_arm = arm;
}

// Called when the command is initially scheduled.
void CmdArmLevelSetPosition::Initialize() 
{

}
