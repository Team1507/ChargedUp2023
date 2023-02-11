// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/Drivetrain.h"

class CmdGyroSetAngleOffset
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdGyroSetAngleOffset> {
 public:
  CmdGyroSetAngleOffset(Drivetrain *drivetrain, float angle);

  void Initialize() override;

  private:

   Drivetrain *m_drivetrain;
   float      m_angle;
};
