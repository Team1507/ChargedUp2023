#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>

#include "subsystems/Claw.h"

class CmdClawIntakeEnable
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdClawIntakeEnable> {
 public:
  CmdClawIntakeEnable(Claw *claw, bool enable);

  void Initialize() override;

  private:
    Claw *m_claw;
    bool m_isEnabled;
};
