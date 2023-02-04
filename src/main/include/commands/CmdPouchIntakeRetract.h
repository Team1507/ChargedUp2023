#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>

#include "subsystems/Pouch.h"

class CmdPouchIntakeRetract
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdPouchIntakeRetract> {
 public:
  CmdPouchIntakeRetract(Pouch *pouch);

  void Initialize() override;

  private:
    Pouch *m_pouch;
};
