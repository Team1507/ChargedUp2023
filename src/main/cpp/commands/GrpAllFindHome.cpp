#include "commands/GrpAllFindHome.h"
#include "commands/CmdTurretSetPower.h"
#include "commands/CmdWristSetPosition.h"
#include "commands/CmdPouchIntakeRetract.h"
#include "commands/CmdArmExtensionSetPosition.h"
#include "commands/CmdArmLevelSetPosition.h"
#include "commands/CmdTurretTurn2Angle.h"
#include "commands/CmdTurretFindHome.h"

#include <frc2/command/WaitCommand.h>

GrpAllFindHome::GrpAllFindHome(Arm *arm, Pouch *pouch, Claw *claw) 
{
  AddCommands(
  CmdArmExtensionSetPosition(arm, false),
  frc2::SequentialCommandGroup
  {

    frc2::WaitCommand(0.5_s),
    frc2::ParallelCommandGroup
    {
        CmdTurretTurn2Angle(arm, 60),
        CmdWristSetPosition(claw, 2),
    },

    // frc2::WaitCommand(0.5_s),
    frc2::ParallelCommandGroup
    {
        CmdArmLevelSetPosition(arm, ArmLevel::Low, pouch),
        CmdTurretTurn2Angle(arm, 5),
    },
//    frc2::WaitCommand(0.5_s),

    frc2::ParallelCommandGroup
    {
        CmdArmLevelSetPosition(arm, ArmLevel::Low, pouch),
        CmdTurretFindHome(arm),
    },
    frc2::WaitCommand(0.25_s),

    CmdArmLevelSetPosition(arm, ArmLevel::Level_Pouch,pouch)
  
  }
  );
}
