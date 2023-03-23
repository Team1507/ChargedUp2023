#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Drivetrain.h"
#include "subsystems/Arm.h"
#include "subsystems/Pouch.h"
#include "subsystems/Claw.h"
class AutoTwoHighBlue
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 AutoTwoHighBlue> {
 public:
  AutoTwoHighBlue(Drivetrain *drivetrain, Pouch *pouch, Arm *arm, Claw *claw);
};
