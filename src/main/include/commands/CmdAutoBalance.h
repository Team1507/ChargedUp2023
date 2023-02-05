#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Timer.h>
#include "subsystems/Drivetrain.h"

class CmdAutoBalance
    : public frc2::CommandHelper<frc2::CommandBase, CmdAutoBalance> {
 public:
  CmdAutoBalance(Drivetrain *drivetrain);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:

    frc::Timer m_timer;
    Drivetrain *m_drivetrain;

    float m_speed;

    int m_offDelayCount;
    int m_speedDelayCount;

    bool m_rev;

    bool m_initial;



};
