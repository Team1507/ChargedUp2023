#pragma once
#include <photonlib/PhotonCamera.h>
#include <frc2/command/SubsystemBase.h>
#include "subsystems/DriverFeedback.h"
#include <units/angle.h>
#include <units/length.h>

enum CameraIndex{AprilTag, Cube, Cone};

class Camera : public frc2::SubsystemBase {
 public:
  Camera(DriverFeedback *driverfeedback);

  void Periodic() override;

  bool IsTarget(void);

  double TargetGetDistance(void);
  float TargetGetYaw(void);
  float TargetGetPitch(void);
  float TargetGetArea(void);

  int AprilTagGetID(void);

  void PipelineSetIndex(CameraIndex index);
  int PipelineGetIndex(void);

  //*********************LIMELIGHT*********************
  double GetLimelightHAngle(void);
  double GetLimelightVAngle(void);
  double GetLimelightDistance(void);
  bool   GetLimelightTargetValid(void);
  
  //void   LimeLight3xMode(bool is3XMode);

  const double LIMELIGHT_ANGLE_TOLERANCE = 1; //CHANGE LATER


 private:

 DriverFeedback *m_driverfeedback;
 bool m_cameradetect;

 photonlib::PhotonCamera camera{"Righty"};

 photonlib::PhotonPipelineResult result;

 photonlib::PhotonTrackedTarget target;

 const units::meter_t CAMERA_HEIGHT = 8.5_in;  //13_in;
 const units::meter_t TARGET_HEIGHT = 18.25_in;

  // Angle between horizontal and the camera.
 const units::radian_t CAMERA_PITCH = 13.0_deg; //6.2_deg;

};
