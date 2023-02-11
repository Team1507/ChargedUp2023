#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Drivetrain.h"
#include "CmdDriveTurn2Angle.h"
/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdDriveTurnTo90
    : public frc2::CommandHelper<frc2::CommandBase, CmdDriveTurnTo90> {
 public:
  CmdDriveTurnTo90(Drivetrain *drivetrain, float power, float angle);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:

  Drivetrain *m_drivetrain;
    float m_power;
    float m_angle;
    float m_calcAngle;


};
