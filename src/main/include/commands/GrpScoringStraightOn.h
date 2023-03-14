#pragma once

#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/Arm.h"
#include "subsystems/Claw.h"
#include "subsystems/Pouch.h"

enum ScoringStraightPosition{MidCone, MidCube, HighCone, HighCube};


class GrpScoringStraightOn

    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 GrpScoringStraightOn> {
 public:
  GrpScoringStraightOn(Arm *arm, Claw *claw,Pouch *pouch, ScoringStraightPosition scoringPosition);


};
