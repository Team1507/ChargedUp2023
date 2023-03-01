#include "commands/GrpAllFindHome.h"
#include "commands/CmdTurretSetPower.h"
#include "commands/CmdWristSetPosition.h"
#include "commands/CmdPouchIntakeRetract.h"
#include "commands/CmdArmExtensionSetPosition.h"
#include "commands/CmdArmLevelSetPosition.h"
#include "commands/CmdTurretTurn2Angle.h"

GrpAllFindHome::GrpAllFindHome(Arm *arm, Pouch *pouch, Claw *claw) 
{
  frc2::SequentialCommandGroup
  {
    frc2::ParallelCommandGroup
    {
        CmdTurretTurn2Angle(arm, 60),
        CmdArmExtensionSetPosition(arm, false),
        CmdWristSetPosition(claw, 0),
    },
    
    frc2::ParallelCommandGroup
    {
        CmdArmLevelSetPosition(arm, ArmLevel::Low, pouch),
        CmdTurretTurn2Angle(arm, 0)
    },
    frc2::SequentialCommandGroup
    {
        CmdArmLevelSetPosition(arm, ArmLevel::Level_Pouch,pouch)
    }    
  };

}
