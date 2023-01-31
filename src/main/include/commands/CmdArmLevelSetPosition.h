#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/Arm.h"
class CmdArmLevelSetPosition
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdArmLevelSetPosition> {
 public:
 
  CmdArmLevelSetPosition(Arm *arm, ArmLevel armLevel);
  
  void Initialize() override;

  private:
    Arm *m_arm;
    ArmLevel m_armLevel;
};
