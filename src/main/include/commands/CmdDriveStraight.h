// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Timer.h>
#include "subsystems\Drivetrain.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdDriveStraight
    : public frc2::CommandHelper<frc2::CommandBase, CmdDriveStraight> {
 public:
  CmdDriveStraight(Drivetrain *drivetrain, float power, float heading, float distance, bool ramp, bool stop, float timeout);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:

  Drivetrain *m_drivetrain;

  frc::Timer m_timer;
  
  float m_power;
  float m_heading;
  float m_distance;
  bool  m_stop;
  bool  m_ramp;
  float m_timeout;   


  float m_initial_x;
  float m_initial_y;


};
