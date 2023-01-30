#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/Arm.h"

class CmdArmExtensionSetPosition
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdArmExtensionSetPosition> {
 public:
  CmdArmExtensionSetPosition(Arm *arm, bool extension);

  void Initialize() override;

  private:
    bool m_isExtension;

    Arm *m_arm;
};
