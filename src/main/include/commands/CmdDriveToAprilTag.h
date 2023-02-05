#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Drivetrain.h"
#include "subsystems/Camera.h"

class CmdDriveToAprilTag
    : public frc2::CommandHelper<frc2::CommandBase, CmdDriveToAprilTag> {
 public:
  CmdDriveToAprilTag(Drivetrain *drivetrain, Camera *Camera,float power);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    float m_power;

    float m_tagAngle;

    float m_calcAngle;
    int m_delay;
    bool m_turnComplete;
    bool m_sideMoveComplete;
    bool m_fwrdMovementComplete;

    Drivetrain *m_drivetrain;
    Camera *m_Camera;
};
