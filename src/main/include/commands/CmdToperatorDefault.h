#include "subsystems/Arm.h"
#include "subsystems/Claw.h"
#include "subsystems/Pouch.h"
#include "subsystems/DriverFeedback.h"
#include "subsystems/Toperator.h"
#include "frc/XboxController.h"
#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdToperatorDefault
    : public frc2::CommandHelper<frc2::CommandBase, CmdToperatorDefault> {
 public:
  CmdToperatorDefault(Toperator *toperator, frc::XboxController *topDriver, Claw *claw, Arm *arm, Pouch *pouch, DriverFeedback *driverfeedback);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    Toperator *m_toperator;
    frc::XboxController *m_topDriver;
    Claw *m_claw;
    Arm *m_arm;
    Pouch *m_pouch;
    DriverFeedback *m_driverFeedback;

    bool m_isIntaking;


};