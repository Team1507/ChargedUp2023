// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/DriverFeedback.h"
#include <frc/XboxController.h>
#include "subsystems/Claw.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdDriverFeedbackDefault
    : public frc2::CommandHelper<frc2::CommandBase, CmdDriverFeedbackDefault> {
 public:
  CmdDriverFeedbackDefault(DriverFeedback *driverfeedback, frc::XboxController *xboxcontroller, Claw *claw);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool m_isPieceCollected;
 
  bool IsFinished() override;
  private:
  bool m_isRumble;
  int  m_delay;
  DriverFeedback *m_driverfeedback;
  frc::XboxController *m_xboxcontroller;
  Claw *m_claw;
};
