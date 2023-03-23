#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/Pouch.h"

class CmdPouchIntakeDeployHalf
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdPouchIntakeDeployHalf> {
 public:
  CmdPouchIntakeDeployHalf(Pouch *pouch);

  void Initialize() override;

  private:
    Pouch *m_pouch;
};
