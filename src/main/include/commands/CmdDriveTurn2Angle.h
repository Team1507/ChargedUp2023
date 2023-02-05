// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems\Drivetrain.h"



/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdDriveTurn2Angle
    : public frc2::CommandHelper<frc2::CommandBase, CmdDriveTurn2Angle> {
 public:
  CmdDriveTurn2Angle(Drivetrain *drivetrain, float power, float angle);

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
