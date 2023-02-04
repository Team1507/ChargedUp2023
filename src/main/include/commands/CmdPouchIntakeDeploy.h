#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/Pouch.h"

class CmdPouchIntakeDeploy
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdPouchIntakeDeploy> {
 public:
  CmdPouchIntakeDeploy(Pouch *pouch);

  void Initialize() override;

  private:
    Pouch *m_pouch;
};
