// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Arm.h"

class CmdTurretTurn2Angle
    : public frc2::CommandHelper<frc2::CommandBase, CmdTurretTurn2Angle> {
 public:
  CmdTurretTurn2Angle(Arm *arm, double angle);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
  private:
  Arm *m_arm;
  double m_angle;
};
