#pragma once
#include <photonlib/PhotonCamera.h>
#include <frc2/command/SubsystemBase.h>
#include <units/angle.h>
#include <units/length.h>

enum CameraIndex{AprilTag, Cube, Cone};

class Camera : public frc2::SubsystemBase {
 public:
  Camera();

  void Periodic() override;

  bool IsTarget(void);

  double TargetGetDistance(void);
  float TargetGetYaw(void);
  float TargetGetPitch(void);
  float TargetGetArea(void);

  int AprilTagGetID(void);

  void PipelineSetIndex(int index);
  int PipelineGetIndex(void);

 private:

 photonlib::PhotonCamera camera{"Righty"};

 photonlib::PhotonPipelineResult result;

 photonlib::PhotonTrackedTarget target;

 const units::meter_t CAMERA_HEIGHT = 13_in;
 const units::meter_t TARGET_HEIGHT = 18.25_in;

  // Angle between horizontal and the camera.
 const units::radian_t CAMERA_PITCH = 6.2_deg;

};
