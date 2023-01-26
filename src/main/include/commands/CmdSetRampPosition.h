
#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/Pouch.h"

class CmdSetRampPosition
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdSetRampPosition> {
 public:
  CmdSetRampPosition(Pouch *pouch, float position);

  void Initialize() override;
Pouch *m_pouch;
float m_position;

};
