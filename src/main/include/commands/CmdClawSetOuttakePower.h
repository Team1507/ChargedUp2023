#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/Claw.h"
class CmdClawSetOuttakePower
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdClawSetOuttakePower> {

 public:
  CmdClawSetOuttakePower(Claw *claw,double power);

  void Initialize() override;
  private:
  Claw *m_claw;
  double m_power;
};
