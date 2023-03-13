#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/Drivetrain.h"
#include "subsystems/Arm.h"
#include "subsystems/Camera.h"
#include "subsystems/Claw.h"
#include "subsystems/Pouch.h"

class AutoPowerStripRed
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 AutoPowerStripRed> {
 public:
  AutoPowerStripRed(Drivetrain *drivetrain, Arm *arm, Camera *camera, Claw *claw, Pouch *pouch );
};
