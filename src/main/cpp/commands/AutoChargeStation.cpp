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
      CmdGyroSetAngleOffset(drivetrain, 0.0),
      frc2::WaitCommand(0.1_s),
      //-------------------------------



      CmdDriveStraightGyro(drivetrain, .3, 90, 90, 30, false, false, 0),
      CmdAutoBalance(drivetrain),


      //-------------------------------
		  CmdPrintText("Auto AutoChargeStation Finish")
    );
}
