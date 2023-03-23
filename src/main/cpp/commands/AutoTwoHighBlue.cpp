#include "commands/AutoTwoHighBlue.h"
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


AutoTwoHighBlue::AutoTwoHighBlue(Drivetrain *drivetrain, Pouch *pouch, Arm *arm, Claw *claw) 
{
    AddCommands
    (
        CmdDriveClearAll(drivetrain),
        CmdGyroSetAngleOffset(drivetrain, 180),
        CmdPouchIntakeDeploy(pouch),
        frc2::WaitCommand(.75_s),
        GrpScoringStraightOn(arm, claw, pouch, ScoringStraightPosition::HighCone),
        CmdWristSetPosition(claw, 17.5),
        frc2::WaitCommand(1.5_s), 
        CmdClawEject(claw),
        CmdArmExtensionSetPosition(arm, false),
        GrpReturnToPouch(arm, pouch, claw),
        frc2::WaitCommand(1.0_s),
        CmdPouchIntakeRetract(pouch),

              
        CmdDriveStraightVelocity(drivetrain, 6400, 10, 0, 24, false, false, 0.0),
        CmdDriveStraightVelocity(drivetrain, 8600, 0, 180, 128, false, false, 0.0),
        CmdPouchIntakeDeploy(pouch),
        CmdDriveStraightVelocity(drivetrain, 6400, 0, 180, 12, false, true, 0.0),
        frc2::WaitCommand(.25_s),
        CmdSetRampPosition(pouch, true),
        CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, .5),
        CmdWristSetPosition(claw, 13.5),
        CmdClawIntakeEnable(claw, true),
        CmdDriveStraightVelocity(drivetrain, 4200, 0, 180, 24, false, true, 0.0),
        frc2::WaitCommand(0.5_s),
        CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, 0),
        CmdPouchIntakeRetract(pouch),
        CmdSetRampPosition(pouch, false),
        CmdDriveStraightVelocity(drivetrain, 6400, -165, 180, 20, false, false, 0.0),
        CmdDriveStraightVelocity(drivetrain, 8600, -172.5, 0, 128, false, false, 0.0),
        CmdPouchIntakeDeploy(pouch),
        CmdDriveStraightVelocity(drivetrain, 4200, 178, 0, 15, false, false, 0.0),
        CmdArmLevelSetPosition(arm, ArmLevel::High, pouch),
        CmdDriveStraightVelocity(drivetrain, 4200, 178, 0, 12, false, true, 0.0),
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
