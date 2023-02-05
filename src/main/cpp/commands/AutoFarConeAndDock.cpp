#include "commands/AutoFarConeAndDock.h"

#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintText.h"

#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveTurn2Angle.h"
#include "commands/CmdAutoBalance.h"
AutoFarConeAndDock::AutoFarConeAndDock( Drivetrain *drivetrain, Arm *arm, Camera *camera, Claw *claw, Pouch *pouch ) 
{
  AddCommands
  (

		  CmdPrintText("Auto AutoFarConeAndDock"),
      //Initial Setup
      CmdDriveClearAll(drivetrain),
      frc2::WaitCommand(0.1_s),
      //-------------------------------

      CmdDriveStraightGyro(drivetrain, .3, -90, 90, 224, false, false, 0.0),
      CmdDriveStraightGyro(drivetrain, .3, 0, 90, 72, false, false, 0.0),
      CmdDriveStraightGyro(drivetrain, .3, 90, 90, 85, false, false, 0.0),
      CmdAutoBalance(drivetrain),

      //-------------------------------
		  CmdPrintText("Auto AutoFarConeAndDock Finish")

  );

}
