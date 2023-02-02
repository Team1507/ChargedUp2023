#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/Arm.h"
#include "subsystems/Claw.h"

enum ScoringPosition{Home, Ready, HighLeft, HighShelf, HighRight, MidLeft, MidShelf, MidRight};


class GrpScoringSetPosition

    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 GrpScoringSetPosition> {
 public:
  GrpScoringSetPosition(Arm *arm, Claw *claw, ScoringPosition scoringPosition);


};
