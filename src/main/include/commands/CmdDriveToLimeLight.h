// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/XboxController.h>
#include "subsystems/Camera.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/DriverFeedback.h"

class CmdDriveToLimeLight
    : public frc2::CommandHelper<frc2::CommandBase, CmdDriveToLimeLight> {
 public:
  CmdDriveToLimeLight(Drivetrain *drivetrain,DriverFeedback *driverFeedback, Camera *Camera, float power);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
  private:
  float m_power;
  int m_count;
  int m_totalMiss;

  Drivetrain *m_drivetrain;
  Camera *m_camera;
  DriverFeedback *m_driverFeedback;
};
