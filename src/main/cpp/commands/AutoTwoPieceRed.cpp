#include "commands/AutoTwoPieceRed.h"


#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintText.h"

#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStraight.h"
#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveTurn2Angle.h"
#include "commands/CmdGyroSetAngleOffset.h"
#include "commands/CmdPouchIntakeDeploy.h"
#include "commands/CmdPouchIntakeSetPower.h"
#include "commands/CmdSetRampPosition.h"
#include "commands/CmdClawIntakeEnable.h"
#include "commands/CmdWristSetPosition.h"
#include "commands/CmdClawSetOuttakePower.h"
#include "commands/CmdClawEject.h"
#include "commands/CmdPouchIntakeRetract.h"
#include "commands/CmdDriveStop.h"
#include "commands/CmdArmLevelSetPosition.h"
#include "commands/CmdArmExtensionSetPosition.h"


AutoTwoPieceRed::AutoTwoPieceRed(Drivetrain *drivetrain, Arm *arm, Camera *camera, Claw *claw, Pouch *pouch) 
{
  AddCommands
  (
	  CmdPrintText("Auto AutoTwoPieceBlue"),
      //Initial Setup
      CmdDriveClearAll(drivetrain),
      CmdGyroSetAngleOffset(drivetrain, 180.0),
      //frc2::WaitCommand(1.0_s),
      //-------------------------------
      CmdPouchIntakeDeploy(pouch),
      frc2::WaitCommand(1.0_s),
      CmdArmLevelSetPosition(arm, ArmLevel::High, pouch, claw),
      frc2::WaitCommand(0.5_s),//was 1.0_s
      //CmdArmExtensionSetPosition(arm, true),
      CmdWristSetPosition(claw, 8),
      frc2::WaitCommand(0.5_s),
      CmdClawSetOuttakePower(claw, -0.6),
      CmdClawEject(claw),
      //CmdArmExtensionSetPosition(arm, false),
      //frc2::WaitCommand(0.5_s),
      CmdArmLevelSetPosition(arm, ArmLevel::Level_Pouch, pouch, claw),
      frc2::WaitCommand(1.0_s),
      CmdPouchIntakeRetract(pouch),
      CmdDriveStraightGyro(drivetrain, .6, 0, 0, 125, false, false, 0.0),

      

      //Deply intakes
      CmdPouchIntakeDeploy(pouch),
      CmdClawIntakeEnable(claw, true),
      CmdWristSetPosition(claw, 11),

      //Turn 180
      CmdDriveTurn2Angle(drivetrain, .3, 180),    

      //Drop Ramp
      CmdSetRampPosition(pouch, true),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, .5),


      // CmdDriveStraightGyro(drivetrain, .2, 90, -180, 3, false, true, 0.0),
      // frc2::WaitCommand(1.0_s),
      // CmdDriveStraightGyro(drivetrain, .2, 0, -180, 27, false, true, 0.0),

      //Go Get that cube!
      CmdDriveStraightGyro(drivetrain, .2, 0, 180, 27, false, true, 0.0),

      frc2::WaitCommand(0.1_s),
      CmdPouchIntakeRetract(pouch),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, 0),
      CmdSetRampPosition(pouch, false),
      frc2::WaitCommand(0.1_s),

      CmdDriveTurn2Angle(drivetrain, .3, 180),

      CmdDriveStraightGyro(drivetrain, .6, 180, 360, 100, false, false, 0.0),

      CmdDriveStraightGyro(drivetrain, .4, 180, 360, 20, false, false, 0.0),

      CmdPouchIntakeDeploy(pouch),

      CmdDriveStraightGyro(drivetrain, .2, 180, 360, 18, false, false, 0.0),

      CmdArmLevelSetPosition(arm, ArmLevel::Mid, pouch, claw),
      CmdWristSetPosition(claw, 2),

      CmdDriveStraightGyro(drivetrain, .2, 180, 360, 26, false, true, 0.0),
      CmdArmExtensionSetPosition(arm, true),
      frc2::WaitCommand(0.2_s),
      CmdClawSetOuttakePower(claw, -.5),
      CmdClawEject(claw),

      CmdArmExtensionSetPosition(arm, false),
      CmdDriveStraightGyro(drivetrain, .1, 0, 360, 10, false, false, 0.0),
      CmdArmLevelSetPosition(arm, ArmLevel::Level_Pouch, pouch, claw),
      CmdDriveStraightGyro(drivetrain, .1, 0, 360, 10, false, true, 0.0),
      CmdPouchIntakeRetract(pouch),



      //E-Stop
      CmdDriveStop(drivetrain), // saftey
      //-------------------------------
	  CmdPrintText("Auto TwoPieceBlue Finish")
  );
}
