// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/GrpTest1.h"
#include "frc2/command/WaitCommand.h"
#include "commands/CmdPrintText.h"


#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStraight.h"
#include "commands/CmdDriveStraightGyro.h"
#include "commands/CmdDriveTurn2Angle.h"
#include "commands/CmdDriveStraightVelocity.h"


GrpTest1::GrpTest1( Drivetrain *drivetrain, Arm *arm, Camera *camera, Claw *claw, Pouch *pouch ) {
  // AddCommands(FooCommand(), BarCommand());

  AddCommands
  (

    CmdPrintText("GrpTest1 Start"),
        

    CmdDriveClearAll(drivetrain),
    frc2::WaitCommand(0.5_s),
    //---------------------------------------



  //                               power, gyroHeading,  gyroYaw, distance,   ramp,    stop,    timeout)
  CmdDriveStraightGyro( drivetrain,  0.2,      0.0,        0.0,     42,       false,   false,     5.0  ),
  CmdDriveStraightGyro( drivetrain,  0.2,    -90.0,        0.0,     42,       false,   false,     5.0  ),
  CmdDriveStraightGyro( drivetrain,  0.2,    180.0,        0.0,     42,       false,   false,     5.0  ),
  CmdDriveStraightGyro( drivetrain,  0.2,     90.0,        0.0,     42,       false,   true,      5.0  ),

  frc2::WaitCommand(0.5_s),

  //                                power, gyroHeading,  gyroYaw, distance,   ramp,    stop,    timeout)
  CmdDriveStraightGyro( drivetrain,  0.2,      0.0,        0.0,     42,       false,   false,     5.0  ),

  //                                power    angle) 
  CmdDriveTurn2Angle( drivetrain,    0.25,    -90.0 ),
  CmdDriveStraightGyro( drivetrain,  0.2,     -90.0,      -90.0,     42,       false,   false,     5.0  ),

  CmdDriveTurn2Angle( drivetrain,    0.25,   -90.0 ),
  CmdDriveStraightGyro( drivetrain,  0.2,     180.0,     -180.0,     42,       false,   false,     5.0  ),

  CmdDriveTurn2Angle( drivetrain,    0.25,    -90.0 ),
  CmdDriveStraightGyro( drivetrain,  0.2,      90.0,     -270.0,     42,       false,   false,     5.0  ),

  CmdDriveTurn2Angle( drivetrain,    0.25,    -90.0),


    //---------------------------------------
    //All Done
    CmdPrintText("GrpTest1 Finished")

  );
}
