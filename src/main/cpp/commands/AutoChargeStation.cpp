#include "commands/AutoChargeStation.h"

#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintText.h"

#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveTurn2Angle.h"
#include "commands/CmdAutoBalance.h"
#include "commands/CmdGyroSetAngleOffset.h"


AutoChargeStation::AutoChargeStation( Drivetrain *drivetrain, Arm *arm, Camera *camera, Claw *claw, Pouch *pouch ) 
{
    AddCommands
    (

	  CmdPrintText("Auto AutoChargeStation"),
      //Initial Setup
      CmdDriveClearAll(drivetrain),
      CmdGyroSetAngleOffset(drivetrain, 90.0),
      frc2::WaitCommand(0.1_s),
      //-------------------------------



      CmdDriveStraightGyro(drivetrain, .3, 0, 0, 26, false, false, 0),
      CmdDriveStraightGyro(drivetrain, .2, 0, 0, 19, false, false, 0),
      CmdDriveStraightGyro(drivetrain, .3, 0, 0, 106, false, false, 0),
      CmdDriveStraightGyro(drivetrain, .2, 180, 0, 15, false, false, 0),
      CmdAutoBalance(drivetrain),


      //-------------------------------
		  CmdPrintText("Auto AutoChargeStation Finish")
    );
}
