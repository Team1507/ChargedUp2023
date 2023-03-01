#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Pouch.h"
#include "subsystems/Arm.h"

class CmdArmLevelSetPosition
    : public frc2::CommandHelper<frc2::CommandBase, CmdArmLevelSetPosition> {
 public:
  CmdArmLevelSetPosition(Arm *arm, ArmLevel armLevel, Pouch *pouch);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
  Arm *m_arm;
  ArmLevel m_armLevel;
  Pouch *m_pouch;
  int m_delay;
};
