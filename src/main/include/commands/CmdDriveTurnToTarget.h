#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Drivetrain.h"
#include "subsystems/Camera.h"

class CmdDriveTurnToTarget
    : public frc2::CommandHelper<frc2::CommandBase, CmdDriveTurnToTarget> {
 public:
  CmdDriveTurnToTarget(Drivetrain *drivetrain, Camera *camera, float power);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    float m_angle;
    float m_power;
    float m_calcAngle;

    Drivetrain *m_drivetrain;
    Camera *m_camera;

};
