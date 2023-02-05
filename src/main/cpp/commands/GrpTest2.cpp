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


GrpTest2::GrpTest2(Drivetrain *drivetrain) {
  // AddCommands(FooCommand(), BarCommand());

  AddCommands
  (

    CmdPrintText("GrpTest2 Start"),
        

    CmdDriveClearAll(drivetrain),
    frc2::WaitCommand(0.5_s),
    //---------------------------------------





    //---------------------------------------
    //All Done
    CmdPrintText("GrpTest2 Finished")

  );
}
