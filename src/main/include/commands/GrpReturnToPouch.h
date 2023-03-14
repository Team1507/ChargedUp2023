// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Claw.h"
#include "subsystems/Pouch.h"
#include "subsystems/Arm.h"


class GrpReturnToPouch
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 GrpReturnToPouch> {
 public:
  GrpReturnToPouch(Arm *arm, Pouch *pouch, Claw *claw);
};
