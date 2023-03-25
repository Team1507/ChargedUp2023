#include "commands/CmdDriveToLimeLight.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

CmdDriveToLimeLight::CmdDriveToLimeLight(Drivetrain *drivetrain,DriverFeedback *driverFeedback, Camera *Camera, float power) 
{
  m_power          = power;
  m_drivetrain     = drivetrain;
  m_camera         = Camera;
  m_driverFeedback = driverFeedback;

  AddRequirements({ drivetrain });
}

void CmdDriveToLimeLight::Initialize() 
{
  m_count = 0;
  m_totalMiss = 0;
}

void CmdDriveToLimeLight::Execute() 
{
  float HAngle = m_camera->GetLimelightHAngle();
  if(HAngle > frc::SmartDashboard::GetNumber("limelight ANGLE_OFFSET",4.2))
  {
    m_drivetrain->RobotcentricDrive(0,m_power, 0);
  }
  else if(HAngle < frc::SmartDashboard::GetNumber("limelight ANGLE_OFFSET",4.2))
  {
    m_drivetrain->RobotcentricDrive(0, -m_power, 0);
  }
  m_count++;
}

void CmdDriveToLimeLight::End(bool interrupted) 
{
  m_drivetrain->RobotcentricDrive(0,0,0);
  std::cout<<"Drive To LimeLight last Angle "<<m_camera->GetLimelightHAngle()<<std::endl;
}

bool CmdDriveToLimeLight::IsFinished() 
{
  double angleOffset    = frc::SmartDashboard::GetNumber("limelight ANGLE_OFFSET",4.2);
  double errorTolorance = frc::SmartDashboard::GetNumber("limelight ERROR_TOLORANCE",0.5);

  if(!m_camera->GetLimelightTargetValid())
  {
    if(m_totalMiss > 5)
    {
      std::cout<<"Lost Target"<<std::endl;
      m_totalMiss = 0;      
      return true;
    }
    else
    {
      m_totalMiss++;
      std::cout<<"Lost Target Total "<<m_totalMiss<<std::endl;
      return false;
    }
  }
  else if((m_camera->GetLimelightHAngle()-angleOffset) < errorTolorance && (m_camera->GetLimelightHAngle()-angleOffset) > -errorTolorance)
  {
    std::cout<<"Finished Line UP"<<std::endl;
    m_driverFeedback->DriverFeedbackLED(COLOR_RED);
    m_driverFeedback->RumbleBot(1.0);
    return true;    
  }    
  else if(m_count > 250)
  {
    std::cout<<"Timeout"<<std::endl;
    return true;
  }
  else
  {
    m_totalMiss=0;
    return false;
  }
}
