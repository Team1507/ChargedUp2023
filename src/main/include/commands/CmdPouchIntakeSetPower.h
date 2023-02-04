#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/Pouch.h"

class CmdPouchIntakeSetPower
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdPouchIntakeSetPower> {
 public:
  CmdPouchIntakeSetPower(Pouch *pouch, Pouch::WhatIntake type, float power);

  void Initialize() override;

  private:
    Pouch *m_pouch;
    float m_power;
    Pouch::WhatIntake m_type;
};
