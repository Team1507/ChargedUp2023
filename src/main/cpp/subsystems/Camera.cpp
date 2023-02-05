#include "subsystems/Camera.h"
#include <photonlib/PhotonUtils.h>
#include <units/angle.h>
#include <units/length.h>
#include <iostream>

Camera::Camera() = default;

void Camera::Periodic() 
{
    result = camera.GetLatestResult(); //checks camera "result", how it gets information
    target = result.GetBestTarget();
}

double Camera::TargetGetDistance(void)
{

    units::meter_t range = photonlib::PhotonUtils::CalculateDistanceToTarget(CAMERA_HEIGHT, TARGET_HEIGHT, CAMERA_PITCH, units::degree_t{result.GetBestTarget().GetPitch()});
    return range.value();
    
}

bool Camera::IsTarget(void)
{
    return result.HasTargets();
}

float Camera::TargetGetYaw(void)
{
    return target.GetYaw();
}

float Camera::TargetGetPitch(void)
{
    return target.GetPitch();
}

float Camera::TargetGetArea(void)
{
    return target.GetArea();
}

int Camera::AprilTagGetID(void)
{
    return target.GetFiducialId();
}

void Camera::PipelineSetIndex(int index)
{
    camera.SetPipelineIndex(index); //Cube = 1  AprilTag = 0  Cone = 2
}


int Camera::PipelineGetIndex(void)
{
    return camera.GetPipelineIndex(); //Cube = 1  AprilTag = 0  Cone = 2
}

