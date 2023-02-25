#include "commands/GrpAllFindHome.h"
#include "commands/CmdTurretSetPower.h"
#include "commands/CmdWristSetPosition.h"
#include "commands/CmdPouchIntakeRetract.h"
#include "commands/CmdArmExtensionSetPosition.h"
#include "commands/CmdArmLevelSetPosition.h"

GrpAllFindHome::GrpAllFindHome(Arm *arm, Pouch *pouch, Claw *claw) 
{
  frc2::SequentialCommandGroup
  {
    CmdArmLevelSetPosition(arm, ArmLevel::Low,pouch),
    
    frc2::ParallelCommandGroup
    {
        CmdArmExtensionSetPosition(arm, false),
        CmdPouchIntakeRetract(pouch),
        CmdTurretSetPower(arm, -.2),
        frc2::SequentialCommandGroup
        {
          CmdArmLevelSetPosition(arm, ArmLevel::Level_Pouch,pouch)
        }
    }
  };

}
