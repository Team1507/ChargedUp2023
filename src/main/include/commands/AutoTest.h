#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Drivetrain.h"
class AutoTest
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 AutoTest> {
 public:
  AutoTest(Drivetrain *drivetrain);
};
