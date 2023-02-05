// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
//Subsystems
#include "subsystems/Drivetrain.h"
#include "subsystems/Arm.h"
#include "subsystems/Camera.h"
#include "subsystems/Claw.h"
#include "subsystems/Pouch.h"

class GrpTest1
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 GrpTest1> {
 public:
  GrpTest1( Drivetrain *drivetrain, Arm *arm, Camera *camera, Claw *claw, Pouch *pouch );
};
