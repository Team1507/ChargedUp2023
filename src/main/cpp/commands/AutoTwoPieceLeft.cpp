#include "commands/AutoTwoPieceLeft.h"

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
#include "commands/CmdPouchIntakeDeploy.h"
#include "commands/CmdPouchIntakeSetPower.h"
#include "commands/CmdPouchIntakeRetract.h"

AutoTwoPieceLeft::AutoTwoPieceLeft(Drivetrain *drivetrain, Arm *arm, Claw *claw, Camera *camera, Pouch *pouch) 
{
AddCommands
    (
      //Initial Setup
      CmdDriveClearAll(drivetrain),
      CmdGyroSetAngleOffset(drivetrain, 90.0),
      frc2::WaitCommand(0.1_s),
      //-------------------------------

    // Score Cone
      GrpScoringSetPosition(arm, claw,pouch, ScoringPosition::HighLeft),
      frc2::WaitCommand(0.5_s),
      CmdClawEject(claw),
      GrpScoringSetPosition(arm, claw,pouch, ScoringPosition::Home),

      //Move to Cube
      CmdDriveStraightGyro(drivetrain, .3, 0, 0, 200, false, false, 0.0),
      CmdPouchIntakeDeploy(pouch),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, .6),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Inner, .3),
      CmdDriveStraightGyro(drivetrain, .3, 0, 0, 24, false, false, 0.0),
      frc2::WaitCommand(1.0_s),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, 0.0),
      CmdPouchIntakeRetract(pouch),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Inner, 0.0),
      CmdDriveStraightGyro(drivetrain, .3, 180, 90, 210, false, false, 0.0),
      CmdDriveToAprilTag(drivetrain, camera, .2),
      GrpScoringSetPosition(arm, claw,pouch, ScoringPosition::HighShelf),
      frc2::WaitCommand(0.5_s),
      CmdClawEject(claw),
      GrpScoringSetPosition(arm, claw,pouch, ScoringPosition::Home),
      CmdDriveStraightGyro(drivetrain, .3, 0, -90, 224, false, false, 0.0),
      CmdPouchIntakeDeploy(pouch),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, .6),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Inner, .3),
      CmdDriveStraightGyro(drivetrain, .3, 90, -90, 48, false, false, 0.0),
      frc2::WaitCommand(1.0_s),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Outer, 0.0),
      CmdPouchIntakeRetract(pouch),
      CmdPouchIntakeSetPower(pouch, Pouch::WhatIntake::Inner, 0.0)

    );
}
