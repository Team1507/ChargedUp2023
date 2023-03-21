#include "subsystems/Camera.h"
#include <photonlib/PhotonUtils.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <units/angle.h>
#include <units/length.h>
#include <iostream>

#define PI 3.1415
#define TARGET_WANTED_AREA 4.0

Camera::Camera(DriverFeedback *driverfeedback)
{
    m_driverfeedback = driverfeedback;
    m_cameradetect = false;

    frc::SmartDashboard::PutNumber("limelight ERROR_TOLORANCE",1.0);
    frc::SmartDashboard::PutNumber("limelight ANGLE_OFFSET",   0.0);
}
void Camera::Periodic() 
{
    if((TargetGetArea() > TARGET_WANTED_AREA) && IsTarget() && !m_cameradetect)
    {
        m_cameradetect = true;
        //m_driverfeedback->DriverFeedbackLED(COLOR_GREEN);
    }
    else if((TargetGetArea() < TARGET_WANTED_AREA) && m_cameradetect)
    {
        m_cameradetect = false;
        //m_driverfeedback->DriverFeedbackLED(COLOR_RED);
    }
    result = camera.GetLatestResult(); //checks camera "result", how it gets information
    target = result.GetBestTarget();
    // std::cout<<Camera::TargetGetYaw()<<std::endl;
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

void Camera::PipelineSetIndex(CameraIndex index)
{
    camera.SetPipelineIndex(index); //Cube = 1  AprilTag = 0  Cone = 2
}


int Camera::PipelineGetIndex(void)
{
    return camera.GetPipelineIndex(); //Cube = 1  AprilTag = 0  Cone = 2
}

//*********************LIMELIGHT*********************

double Camera::GetLimelightHAngle(void)
{
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight-a")->GetNumber("tx", 0);
}
double Camera::GetLimelightVAngle(void)
{

    return nt::NetworkTableInstance::GetDefault().GetTable("limelight-a")->GetNumber("ty", 0);    
}
double Camera::GetLimelightDistance(void)
{
    const double a1 = 32;//angle of limelight 32 off of vertical
    const double h1 = 35.5;//height of limelight from ground
    const double h2 = 103.50;//height of target

    double a2 = nt::NetworkTableInstance::GetDefault().GetTable("limelight-a")->GetNumber("ty", 0);
    
    return (h2-h1)/tan((a1+a2)*(PI/180));
}
bool Camera::GetLimelightTargetValid(void)
{
    return (bool)nt::NetworkTableInstance::GetDefault().GetTable("limelight-a")->GetNumber("tv", 0);
}
void Camera::LimeLightEnable(bool state)
{
    if(state)
    {
        nt::NetworkTableInstance::GetDefault().GetTable("limelight-a")->PutNumber("ledMode",3);
    }
    else if(!state)
    {
        nt::NetworkTableInstance::GetDefault().GetTable("limelight-a")->PutNumber("ledMode",1);
    }
}


// void Shooter::LimeLight3xMode(bool is3xMode)
// {
//     if(is3xMode)
//     {
//         nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 1);
//     }1
//     else
//     {
//         nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 0);
//     }
// }
