
#include "commands/AutoMoveToCone.h"

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

AutoMoveToCone::AutoMoveToCone( Drivetrain *drivetrain, Arm *arm, Camera *camera, Claw *claw, Pouch *pouch ) 
{
  AddCommands
  (
		  CmdPrintText("Auto AutoMoveToCone"),
      //Initial Setup
      CmdDriveClearAll(drivetrain),
      CmdGyroSetAngleOffset(drivetrain, 180.0),
      frc2::WaitCommand(1.0_s),
      //-------------------------------
      CmdWristSetPosition(claw, 3.0),
      CmdClawSetOuttakePower(claw, -.8),
      CmdSetRampPosition(pouch, true),
      CmdClawEject(claw),
      CmdSetRampPosition(pouch, false),
      //CmdDriveStraightGyro(drivetrain, .4, 0, 0, 10, false, false, 0.0),
      CmdDriveStraightGyro(drivetrain, .6, 0, 0, 135, false, false, 0.0),
      CmdDriveTurn2Angle(drivetrain, .3, -180),

      CmdPouchIntakeDeploy(pouch),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, .5),
      CmdSetRampPosition(pouch, true),
      CmdClawIntakeEnable(claw, true),
      CmdWristSetPosition(claw, 11),
      CmdDriveStraightGyro(drivetrain, .2, 90, -180, 3, false, true, 0.0),
      frc2::WaitCommand(1.0_s),
      CmdDriveStraightGyro(drivetrain, .2, 0, -180, 30, false, true, 0.0),
      frc2::WaitCommand(1.0_s),
      CmdPouchIntakeRetract(pouch),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, 0),
      CmdSetRampPosition(pouch, false),
      frc2::WaitCommand(1.0_s),

      CmdDriveTurn2Angle(drivetrain, .3, -175),
      CmdWristSetPosition(claw, 2),
      CmdDriveStraightGyro(drivetrain, .6, -175, -355, 120, false, true, 0.0),
      CmdSetRampPosition(pouch, true),
      CmdClawEject(claw),
      CmdSetRampPosition(pouch, false),

      //E-Stop
      CmdDriveStop(drivetrain), // safety
      
      //-------------------------------
		  CmdPrintText("Auto AutoMoveToCone Finish")
  );
}
