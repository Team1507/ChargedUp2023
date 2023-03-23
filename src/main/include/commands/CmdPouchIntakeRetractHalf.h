// Copyright (c) FIRST and other WPILib contributors.
#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>

#include "subsystems/Pouch.h"

class CmdPouchIntakeRetractHalf
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdPouchIntakeRetractHalf> {
 public:
  CmdPouchIntakeRetractHalf(Pouch *pouch);

  void Initialize() override;

  private:
    Pouch *m_pouch;
};
