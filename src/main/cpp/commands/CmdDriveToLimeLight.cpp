#include "commands/CmdDriveToLimeLight.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

#define ERROR_TOLORANCE 1.0
#define ANGLE_OFFSET 0.0

CmdDriveToLimeLight::CmdDriveToLimeLight(Drivetrain *drivetrain, Camera *Camera,frc::XboxController *driver, float power) 
{
  m_power      = power;
  m_drivetrain = drivetrain;
  m_camera     = Camera;
  m_driver     = driver;


  AddRequirements({ drivetrain });
}

void CmdDriveToLimeLight::Initialize() 
{
  m_count = 0;
}

void CmdDriveToLimeLight::Execute() 
{
  float HAngle = m_camera->GetLimelightHAngle();
  if(HAngle > frc::SmartDashboard::GetNumber("limelight ERROR_TOLORANCE",1.0))
  {
    m_drivetrain->RobotcentricDrive(-m_power, 0, 0);
  }
  else if(HAngle < -frc::SmartDashboard::GetNumber("limelight ERROR_TOLORANCE",1.0))
  {
    m_drivetrain->RobotcentricDrive(m_power, 0, 0);
  }
  m_count++;
}

void CmdDriveToLimeLight::End(bool interrupted) 
{
  m_drivetrain->RobotcentricDrive(0,0,0);
}

bool CmdDriveToLimeLight::IsFinished() 
{
  double angleOffset    = frc::SmartDashboard::GetNumber("limelight ANGLE_OFFSET",0.0);
  double errorTolorance = frc::SmartDashboard::GetNumber("limelight ERROR_TOLORANCE",1.0);

  if((m_camera->GetLimelightHAngle()+angleOffset) < errorTolorance && (m_camera->GetLimelightHAngle()+angleOffset) > -errorTolorance)
  {
    std::cout<<"Finished Line UP"<<std::endl;
    return true;    
  }    
  else if(m_count > 250)
  {
    std::cout<<"Timeout"<<std::endl;
    return true;
  }
  else if(!m_camera->GetLimelightTargetValid())
  {
    std::cout<<"Lost Target"<<std::endl;
    return true;
  }
  else if(m_driver->GetXButton())
  {
    std::cout<<"Killed by Driver"<<std::endl;
    return true;
  }
  else
  {
    return false;
  }
}
