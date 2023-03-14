#pragma once
#include "subsystems/Claw.h"
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class CmdClawDefault
    : public frc2::CommandHelper<frc2::CommandBase, CmdClawDefault> {
 public:
  CmdClawDefault(Claw *claw);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:

Claw *m_claw;

bool m_isIntaking;
bool m_isOverride;
int m_delay;

};
