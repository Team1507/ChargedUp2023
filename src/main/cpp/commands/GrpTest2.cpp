// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/GrpTest2.h"
#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintText.h"


#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStraight.h"
#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveTurn2Angle.h"
#include "commands/CmdIntakeSetEnable.h"
#include "commands/CmdSetRampPosition.h"
//Camera *camera,

GrpTest2::GrpTest2( Drivetrain *drivetrain, Arm *arm,  Claw *claw, Pouch *pouch ) {
  // AddCommands(FooCommand(), BarCommand());

  AddCommands
  (

    CmdPrintText("GrpTest2 Start"),
        

    CmdDriveClearAll(drivetrain),
    frc2::WaitCommand(0.5_s),
    //---------------------------------------
    CmdSetRampPosition(pouch,true),
    frc2::WaitCommand(1_s),

    CmdIntakeSetEnable(pouch,true),




    //---------------------------------------
    //All Done
    CmdPrintText("GrpTest2 Finished")

  );
}
