#include "commands/AutoChargeStation.h"

#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintText.h"

#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveTurn2Angle.h"
#include "commands/CmdAutoBalance.h"
#include "commands/CmdGyroSetAngleOffset.h"

#include "commands/CmdPouchIntakeDeploy.h"
#include "commands/CmdArmLevelSetPosition.h"
#include "commands/CmdArmExtensionSetPosition.h"
#include "commands/CmdWristSetPosition.h"
#include "commands/CmdClawEject.h"
#include "commands/CmdClawSetOuttakePower.h"
#include "commands/CmdPouchIntakeRetract.h"
#include "commands/CmdDriveStop.h"
#include "commands/CmdPouchIntakeDeployHalf.h"
#include "commands/CmdPouchIntakeRetractHalf.h"


AutoChargeStation::AutoChargeStation( Drivetrain *drivetrain, Arm *arm, Camera *camera, Claw *claw, Pouch *pouch ) 
{
    AddCommands
    (

	  CmdPrintText("Auto AutoChargeStation"),
      //Initial Setup
      CmdDriveClearAll(drivetrain),
      CmdGyroSetAngleOffset(drivetrain, 180.0),
      frc2::WaitCommand(0.1_s),
      //-------------------------------


    //Works
    //   CmdDriveStraightGyro(drivetrain, .2,  0,   -90, 23,  false, false, 0),
    //   CmdDriveStraightGyro(drivetrain, .2,  0,   -90, 19,  false, false, 0),
    //   CmdDriveStraightGyro(drivetrain, .35, 0,   -90, 109, false, false, 0),
    //   CmdDriveStraightGyro(drivetrain, .2,  180, -90, 21,  false, false, 0),
    //   CmdAutoBalance(drivetrain),

      //Score Cube High
      CmdPouchIntakeDeployHalf(pouch),
      frc2::WaitCommand(0.75_s),
      CmdArmLevelSetPosition(arm, ArmLevel::High, pouch, claw),
      frc2::WaitCommand(0.5_s),
      CmdWristSetPosition(claw, 10), //was 8
      frc2::WaitCommand(0.5_s),
      CmdClawSetOuttakePower(claw, -0.6),
      CmdClawEject(claw),

      //Return To Pouch
      CmdArmLevelSetPosition(arm, ArmLevel::Level_Pouch, pouch, claw),
      frc2::WaitCommand(1.0_s),
      CmdPouchIntakeRetractHalf(pouch),


      
      //Charge Up!
      CmdDriveStraightGyro(drivetrain, .2,  0,     0, 23,  false, false, 0),
      CmdDriveStraightGyro(drivetrain, .2,  0,     0, 19,  false, false, 0),
      CmdDriveStraightGyro(drivetrain, .35, 0,   -90, 105, false, true, 0),
      frc2::WaitCommand(0.5_s),
      CmdDriveStraightGyro(drivetrain, .2,  180, -90, 21,  false, false, 0),
      CmdAutoBalance(drivetrain),
      frc2::WaitCommand(5.0_s),
      

      //-------------------------------
      //CmdDriveStop(drivetrain), //SAFETY
		  CmdPrintText("Auto AutoChargeStation Finish")
    );
}
