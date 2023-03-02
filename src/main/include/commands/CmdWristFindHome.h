#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Claw.h"

class CmdWristFindHome
    : public frc2::CommandHelper<frc2::CommandBase, CmdWristFindHome> {
 public:
  CmdWristFindHome(Claw *claw);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    Claw *m_claw;
};
