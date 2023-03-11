#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Pouch.h"

class CmdPouchInnerIntakeRotate
    : public frc2::CommandHelper<frc2::CommandBase, CmdPouchInnerIntakeRotate> {
 public:
  CmdPouchInnerIntakeRotate(Pouch *pouch);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
  Pouch *m_pouch;
  double m_startingPosition;
};
