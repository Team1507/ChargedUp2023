#include "commands/AutoPowerStripRed.h"

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
#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintText.h"


AutoPowerStripRed::AutoPowerStripRed(Drivetrain *drivetrain, Arm *arm, Camera *camera, Claw *claw, Pouch *pouch) 
{
AddCommands
    (
      CmdPrintText("Auto AutoPowerStripBlue"),
      //Initial Setup
      CmdDriveClearAll(drivetrain),
      CmdGyroSetAngleOffset(drivetrain, 180.0),

      //Score Cube High
      CmdPouchIntakeDeploy(pouch),
      frc2::WaitCommand(1.0_s),
      CmdArmLevelSetPosition(arm, ArmLevel::High, pouch),
      frc2::WaitCommand(0.5_s),
      CmdWristSetPosition(claw, 8),
      frc2::WaitCommand(0.5_s),
      CmdClawSetOuttakePower(claw, -0.6),
      CmdClawEject(claw),
      //Return Arm Home
      CmdArmLevelSetPosition(arm, ArmLevel::Level_Pouch, pouch),
      frc2::WaitCommand(1.0_s),
      CmdPouchIntakeRetract(pouch),

      CmdDriveStraightGyro(drivetrain, .4, 0, 0, 145, false, true, 0.0),


      //Deeply intakes
      CmdPouchIntakeDeploy(pouch),
      CmdClawIntakeEnable(claw, true),
      CmdWristSetPosition(claw, 11),

      //Turn 180
      CmdDriveTurn2Angle(drivetrain, .3, -180),    

      //Drop Ramp
      CmdSetRampPosition(pouch, true),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, .5),

      // Pick Up Piece
      CmdDriveStraightGyro(drivetrain, .2, 0, -180, 35, false, true, 0.0),

      //Bring everything back in
      frc2::WaitCommand(0.1_s),
      CmdPouchIntakeRetract(pouch),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, 0),
      CmdSetRampPosition(pouch, false),
      frc2::WaitCommand(0.1_s),

      //Driving Back
      CmdDriveStraightGyro(drivetrain, .4, -180, -180, 155, false, false, 0.0),
      
      //Swirly Part
      CmdDriveTurn2Angle(drivetrain, .3, -180),    
      //
      CmdWristSetPosition(claw,2.0),
      //Moving to April Tag 
      CmdDriveStraightGyro(drivetrain, .3, -180, -360, 15, false, true, 0.0),

      //Score Low
      CmdSetRampPosition(pouch, true),
      CmdClawEject(claw),
      CmdSetRampPosition(pouch, false),
      //E-Stop
      CmdDriveStop(drivetrain), // saftey

      CmdPrintText("Auto AutoPowerStripBlue Finish")
    );
}
