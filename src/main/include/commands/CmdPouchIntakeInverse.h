#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Pouch.h"


class CmdPouchIntakeInverse
    : public frc2::CommandHelper<frc2::CommandBase, CmdPouchIntakeInverse> {
 public:
  CmdPouchIntakeInverse(Pouch *pouch, float power);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
  private:

  Pouch *m_pouch;
  float m_power;
  float m_prevPower;

};
