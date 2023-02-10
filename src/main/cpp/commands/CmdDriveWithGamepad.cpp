// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveWithGamepad.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Robot.h"

#include <iostream>

#define VELOCITY_CONTROL_MODE    //Uncomment for Velocity Control Mode

CmdDriveWithGamepad::CmdDriveWithGamepad(Drivetrain *drivetrain, frc::XboxController *botDriver)
{
  m_drivetrain = drivetrain;
  m_botDriver  = botDriver;

  frc::SmartDashboard::PutNumber("Comb the desert Translation Speed Max",0.2);
  frc::SmartDashboard::PutNumber("Comb the desert Rotational Speed Max",0.2);  

  frc::SmartDashboard::PutNumber("Normal Translation Speed Max",0.5);
  frc::SmartDashboard::PutNumber("Normal Rotational Speed Max",0.3);

  frc::SmartDashboard::PutNumber("Ludicrous Translation Speed Max",0.8);
  frc::SmartDashboard::PutNumber("Ludicrous Rotational Speed Max",0.4);

  AddRequirements({ drivetrain });

#ifdef VELOCITY_CONTROL_MODE
  std::cout<<"CmdDriveWithGamepad: Velocity Control"<<std::endl;
#else
  std::cout<<"CmdDriveWithGamepad: Power Control"<<std::endl;
#endif

  
}


void CmdDriveWithGamepad::Initialize() 
{
  std::cout<<"Starting CmdDriveWithGamepad"<<std::endl;
}


void CmdDriveWithGamepad::Execute() 
{



  //Get Gamepad Inputs
  float yL = m_botDriver->GetLeftY();
  float xL = m_botDriver->GetLeftX();
  float xR = m_botDriver->GetRightX();
  bool  BrakeActivated = m_botDriver->GetBackButton();
  bool  BrakePressed   = m_botDriver->GetBButton();


#ifndef VELOCITY_CONTROL_MODE
//***** POWER CONTROL MODE ******

  //Limiters
  float xyScaleValue;
  float rScaleValue;
  float combTranslation =  frc::SmartDashboard::GetNumber("Comb the desert Translation Speed Max",0.2);
  float combRotational  =  frc::SmartDashboard::GetNumber("Comb the desert Rotational Speed Max",0.2);  

  float normalTranslation =  frc::SmartDashboard::GetNumber("Normal Translation Speed Max",0.5);
  float normalRotational  =  frc::SmartDashboard::GetNumber("Normal Rotational Speed Max",0.3);

  float ludicrousTranslation =  frc::SmartDashboard::GetNumber("Ludicrous Translation Speed Max",0.8);
  float ludicrousRotational  =  frc::SmartDashboard::GetNumber("Ludicrous Rotational Speed Max",0.4);


  bool ludicrous = m_botDriver->GetLeftTriggerAxis()>0.5;
  bool comb      = m_botDriver->GetRightTriggerAxis()>0.5;
  if(comb)
  {
    xyScaleValue = combTranslation;
    rScaleValue  = combRotational;
  }
  else if(ludicrous)
  {
    xyScaleValue = ludicrousTranslation;
    rScaleValue  = ludicrousRotational;
  }
  else
  {
    xyScaleValue = normalTranslation;
    rScaleValue  = normalRotational;
  }

  //Scalers
  yL *= -xyScaleValue;    //Invert Axis, make positive forward
  xL *=  xyScaleValue;    
  xR *= -rScaleValue;     //Invert Axis, make positive CCW

  //Run depending on Mode:  

  if( m_drivetrain->GetDriveType() == Drivetrain::ROBOTCENTRIC )
    m_drivetrain->RobotcentricDrive( yL,  xL,  xR );
  else
    m_drivetrain->FieldcentricDrive( yL,  xL,  xR );

#endif

#ifdef VELOCITY_CONTROL_MODE 

//***** VELOCITY CONTROL MODE ******

  const float xyMaxVelocity = 19600; //
  const float rMaxVelocity  = 13000; //


 //Limiters
  float xyScaleValue;
  float rScaleValue;
  float combTranslation      =  frc::SmartDashboard::GetNumber("Comb the desert Translation Speed Max",0.2);
  float combRotational       =  frc::SmartDashboard::GetNumber("Comb the desert Rotational Speed Max",0.2);  

  float normalTranslation    =  frc::SmartDashboard::GetNumber("Normal Translation Speed Max",0.5);
  float normalRotational     =  frc::SmartDashboard::GetNumber("Normal Rotational Speed Max",0.3);

  float ludicrousTranslation =  frc::SmartDashboard::GetNumber("Ludicrous Translation Speed Max",0.8);
  float ludicrousRotational  =  frc::SmartDashboard::GetNumber("Ludicrous Rotational Speed Max",0.4);


  bool ludicrous = m_botDriver->GetLeftTriggerAxis()>0.5;
  bool comb      = m_botDriver->GetRightTriggerAxis()>0.5;
  if(comb)
  {
    xyScaleValue = combTranslation;
    rScaleValue  = combRotational;
  }
  else if(ludicrous)
  {
    xyScaleValue = ludicrousTranslation;
    rScaleValue  = ludicrousRotational;
  }
  else
  {
    xyScaleValue = normalTranslation;
    rScaleValue  = normalRotational;
  }



  yL *= -(xyMaxVelocity * xyScaleValue);    //Invert Axis, make positive forward
  xL *=  (xyMaxVelocity * xyScaleValue);    
  xR *= -(rMaxVelocity  * rScaleValue);     //Invert Axis, make positive CCW

  if( m_drivetrain->GetDriveType() == Drivetrain::ROBOTCENTRIC )
    m_drivetrain->RobotcentricDriveVelocity( yL,  xL,  xR );
  else
    m_drivetrain->FieldcentricDriveVelocity( yL,  xL,  xR );

#endif


  //SwerveDrive BreakMode
  if(BrakeActivated && BrakePressed)
  {
    m_drivetrain->ForcePark();
  }

}


void CmdDriveWithGamepad::End(bool interrupted) 
{
  std::cout<<"End CmdDriveWithGamepad " << interrupted <<std::endl;
}


bool CmdDriveWithGamepad::IsFinished() 
{
  return false;
}
