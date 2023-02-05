#include "commands/AutoOverAndBack.h"

#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintText.h"

#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveTurn2Angle.h"
#include "commands/CmdAutoBalance.h"

AutoOverAndBack::AutoOverAndBack( Drivetrain *drivetrain, Arm *arm, Camera *camera, Claw *claw, Pouch *pouch ) 
{
    AddCommands
    (

		  CmdPrintText("Auto AutoOverAndBack"),
      //Initial Setup
      CmdDriveClearAll(drivetrain),
      frc2::WaitCommand(0.1_s),
      //-------------------------------



      CmdDriveStraightGyro(drivetrain, .3, 90, 90, 160, false, false, 0),
      CmdDriveTurn2Angle(drivetrain,.3, -180),
      CmdDriveStraightGyro(drivetrain,.3, 90, -90, 44, false, true, 0.0 ),
      frc2::WaitCommand(0.5_s),
      CmdDriveStraightGyro(drivetrain,.3, -90, -90, 85, false, false, 0),
      CmdAutoBalance(drivetrain),
      
      
      //-------------------------------
		  CmdPrintText("Auto AutoOverAndBack Finish")
    );
}
