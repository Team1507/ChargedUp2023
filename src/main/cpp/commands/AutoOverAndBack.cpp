#include "commands/AutoOverAndBack.h"

#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintText.h"

#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveStraightVelocity.h"
#include "commands/CmdDriveTurn2Angle.h"
#include "commands/CmdGyroSetAngleOffset.h"
#include "commands/CmdAutoBalance.h"
#include "commands/CmdDriveToAprilTag.h"
#include "commands/GrpScoringSetPosition.h"
#include "commands/CmdClawEject.h"
AutoOverAndBack::AutoOverAndBack( Drivetrain *drivetrain, Arm *arm, Camera *camera, Claw *claw, Pouch *pouch ) 
{
    AddCommands
    (

	  CmdPrintText("Auto AutoOverAndBack"),
      //Initial Setup
      CmdDriveClearAll(drivetrain),
      CmdGyroSetAngleOffset(drivetrain, 90.0),
      frc2::WaitCommand(0.1_s),
      //-------------------------------

    // Score Cone
      GrpScoringSetPosition(arm, claw, ScoringPosition::HighLeft),
      frc2::WaitCommand(0.5_s),
      CmdClawEject(claw),
      GrpScoringSetPosition(arm, claw, ScoringPosition::Home),
    // Move to Cube over Charge Station
      CmdDriveStraightGyro(drivetrain, .3, 0, 180, 160, false, false, 0.0),
      CmdDriveTurn2Angle(drivetrain,.3, -180),
      CmdDriveStraightGyro(drivetrain,.3, 0, 00, 44, false, true, 0.0 ),
      frc2::WaitCommand(0.5_s),
    //Come Back To Score
      CmdDriveStraightGyro(drivetrain, .3, 180, 0, 150, false, false, 0.0),
      CmdDriveTurn2Angle(drivetrain, .3, 90),
      CmdDriveToAprilTag(drivetrain, camera, .3),
    // Score Cube
      GrpScoringSetPosition(arm, claw, ScoringPosition::HighShelf),
      frc2::WaitCommand(0.5_s),
      CmdClawEject(claw),
      GrpScoringSetPosition(arm, claw, ScoringPosition::Home),
    // CHARGE
      CmdDriveStraightGyro(drivetrain, .3, 0, 180, 60, false, false, 0.0),
      CmdAutoBalance(drivetrain),



      
      
      //-------------------------------
	  CmdPrintText("Auto AutoOverAndBack Finish")
    );
}
