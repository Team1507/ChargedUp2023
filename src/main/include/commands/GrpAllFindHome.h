#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Claw.h"
#include "subsystems/Pouch.h"
#include "subsystems/Arm.h"

class GrpAllFindHome
    : public frc2::CommandHelper<frc2::ParallelCommandGroup,
                                 GrpAllFindHome> {
 public:
  GrpAllFindHome(Arm *arm, Pouch *pouch, Claw *claw);
};
