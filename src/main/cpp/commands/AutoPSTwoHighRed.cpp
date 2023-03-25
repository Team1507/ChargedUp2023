#include "commands/AutoPSTwoHighRed.h"

#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintText.h"

#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStraight.h"
#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveStraightVelocity.h"
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
#include "commands/GrpScoringStraightOn.h"
#include "commands/GrpReturnToPouch.h"
#include "commands/CmdPouchIntakeDeployHalf.h"
#include "commands/CmdPouchIntakeRetractHalf.h"



AutoPSTwoHighRed::AutoPSTwoHighRed(Drivetrain *drivetrain, Pouch *pouch, Arm *arm, Claw *claw) 
{
AddCommands
    (
        //Score Cone High
        CmdDriveClearAll(drivetrain),
        CmdGyroSetAngleOffset(drivetrain, 180),
        CmdPouchIntakeDeployHalf(pouch),
        frc2::WaitCommand(.75_s),
        GrpScoringStraightOn(arm, claw, pouch, ScoringStraightPosition::HighCone),
        CmdWristSetPosition(claw, 17.5),
        frc2::WaitCommand(1.5_s), 
        CmdClawEject(claw),

        //Return to Home
        CmdArmExtensionSetPosition(arm, false),
        GrpReturnToPouch(arm, pouch, claw),
        frc2::WaitCommand(0.75_s),
        CmdPouchIntakeRetractHalf(pouch),

        // Drive and Spin to Cube
        CmdDriveStraightVelocity(drivetrain, 6400, 7, 0, 24, false, false, 0.0),
        CmdDriveStraightVelocity(drivetrain, 8600, 0, 180, 128, false, false, 0.0),

        //Deploy & Run Intakes
        CmdPouchIntakeDeploy(pouch),
        CmdDriveStraightVelocity(drivetrain, 6400, 0, 180, 12, false, true, 0.0),
        frc2::WaitCommand(.25_s),
        CmdSetRampPosition(pouch, true),
        CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, .5),
        CmdWristSetPosition(claw, 11),
        CmdClawIntakeEnable(claw, true),

        //Pick Cube Up
        CmdDriveStraightVelocity(drivetrain, 4200, 0, 180, 26, false, true, 0.0),
        frc2::WaitCommand(0.5_s),

        //Stop Intakes and bring it in
        CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, 0),
        CmdPouchIntakeRetract(pouch),
        CmdSetRampPosition(pouch, false),
        CmdClawIntakeEnable(claw, false),

        //Drive and Spin back to Shelf
        CmdDriveStraightVelocity(drivetrain, 6400, -165, 180, 20, false, false, 0.0),
        CmdDriveStraightVelocity(drivetrain, 8600, -172.5, 0, 128, false, false, 0.0),

        //Get Ready to Score
        CmdPouchIntakeDeployHalf(pouch),
        CmdDriveStraightVelocity(drivetrain, 4200, 178, 0, 25, false, true, 0.0),
        CmdWristSetPosition(claw, 2),
        frc2::WaitCommand(.1_s),
        //Score that Cube
        CmdArmLevelSetPosition(arm, ArmLevel::Mid, pouch, claw),
        CmdDriveStraightVelocity(drivetrain, 4200, 178, 0, 17, false, true, 0.0),

        //CmdArmExtensionSetPosition(arm, true),
        
        CmdClawSetOuttakePower(claw, -0.5),
        frc2::WaitCommand(0.25_s),
        CmdClawEject(claw),
        CmdArmExtensionSetPosition(arm, false),
        //frc2::WaitCommand(0.3_s),
        CmdArmLevelSetPosition(arm, ArmLevel::Level_Pouch, pouch, claw),
        CmdDriveStraightVelocity(drivetrain, 6400, 0, 0, 25, false, false, 0.0),
        CmdDriveStraightVelocity(drivetrain, 13000, 0, 0, 75, false, true, 0.0),
        // frc2::WaitCommand(0.5_s),//was 1.0_s
        // CmdArmExtensionSetPosition(arm, true),
        // CmdWristSetPosition(claw, 8),
        // frc2::WaitCommand(0.5_s),
        // CmdClawSetOuttakePower(claw, -0.6),
        // CmdClawEject(claw),
        // CmdDriveStraightVelocity(drivetrain, 8600, 170, 360, 160, false, true, 0.0),
        CmdDriveStop(drivetrain)
    );
}
