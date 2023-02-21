#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Drivetrain.h"
#include "subsystems/Arm.h"
#include "subsystems/Claw.h"
#include "subsystems/Camera.h"
#include "subsystems/Pouch.h"


class AutoTwoPieceRight
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 AutoTwoPieceRight> {
 public:
  AutoTwoPieceRight(Drivetrain *drivetrain, Arm *arm, Claw *claw, Camera *camera, Pouch *pouch);
};
