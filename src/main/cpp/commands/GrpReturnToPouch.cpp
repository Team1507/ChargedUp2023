#include "commands/GrpReturnToPouch.h"

#include "commands/CmdTurretSetPower.h"
#include "commands/CmdWristSetPosition.h"
#include "commands/CmdPouchIntakeRetract.h"
#include "commands/CmdArmExtensionSetPosition.h"
#include "commands/CmdArmLevelSetPosition.h"
#include "commands/CmdTurretTurn2Angle.h"
#include "commands/CmdTurretFindHome.h"
#include "commands/CmdPrintText.h"

#include <frc2/command/WaitCommand.h>



GrpReturnToPouch::GrpReturnToPouch(Arm *arm, Pouch *pouch, Claw *claw) 
{
  AddCommands
  (
    // CmdTurretFindHome(arm),
    frc2::WaitCommand(0.5_s),
    CmdArmLevelSetPosition(arm, ArmLevel::Level_Pouch, pouch, claw),
    CmdWristSetPosition(claw, -1),
    CmdPrintText("ReturnToPouch Done")
  );
}
