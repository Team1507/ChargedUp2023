
#include "commands/AutoMoveToCone.h"

#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintText.h"

#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStraight.h"
#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveTurn2Angle.h"

AutoMoveToCone::AutoMoveToCone( Drivetrain *drivetrain, Arm *arm, Camera *camera, Claw *claw, Pouch *pouch ) 
{
  AddCommands
  (
		  CmdPrintText("Auto AutoMoveToCone"),
      //Initial Setup
      CmdDriveClearAll(drivetrain),
      frc2::WaitCommand(0.1_s),
      //-------------------------------

      CmdDriveStraightGyro(drivetrain, .2, 0, 0, 224.0, false, true, 0.0),
      CmdDriveStraightGyro(drivetrain, .2, 180, 0, 224.0, false, true, 0.0),


      //-------------------------------
		  CmdPrintText("Auto AutoMoveToCone Finish")
  );
}
