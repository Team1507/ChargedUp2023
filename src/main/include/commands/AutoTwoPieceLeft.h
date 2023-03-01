#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>


#include "subsystems/Drivetrain.h"
#include "subsystems/Arm.h"
#include "subsystems/Claw.h"
#include "subsystems/Camera.h"
#include "subsystems/Pouch.h"

class AutoTwoPieceLeft
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 AutoTwoPieceLeft> {
 public:
  AutoTwoPieceLeft(Drivetrain *drivetrain, Arm *arm, Claw *claw, Camera *camera, Pouch *pouch);
};
