#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Timer.h>
#include "subsystems/Drivetrain.h"

class CmdAutoBalanceAlt
    : public frc2::CommandHelper<frc2::CommandBase, CmdAutoBalanceAlt> {
 public:
  CmdAutoBalanceAlt(Drivetrain *drivetrain);

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
    int m_checkDelay;

    bool m_rev;
    bool m_check;

    bool m_initial;



};
