// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveStraight.h"
#include "Robot.h"

#include <iostream>
#include <math.h>

CmdDriveStraight::CmdDriveStraight(Drivetrain *drivetrain, float power, float heading, float distance, bool ramp, bool stop, float timeout)
{

  // ** ROBOT CENTRIC **
  // Heading is referenced to the front of the robot
  //   Heading is the direction the robot is moving with respect to the front of the robot

  m_power    = power;
  m_heading  = heading * M_PI/180.0;  //Convert to radians
  m_distance = distance;
  m_stop     = stop;
  m_timeout  = timeout;
  m_ramp     = ramp;

  m_drivetrain = drivetrain;


  m_initial_x = 0;
  m_initial_y = 0;

  AddRequirements({ drivetrain });
}


void CmdDriveStraight::Initialize() 
{

  m_initial_x = m_drivetrain->GetOdometryX();
  m_initial_y = m_drivetrain->GetOdometryY();

  if( m_timeout > 0.0 )
  {
      m_timer.Reset();
      m_timer.Start();
  }

}


void CmdDriveStraight::Execute() 
{

  float drive_power = m_power;
  
  float y_power = drive_power * cosf(m_heading);
  float x_power = drive_power * sinf(m_heading);

  m_drivetrain->RobotcentricDrive(y_power,x_power,0.0);

}


void CmdDriveStraight::End(bool interrupted) 
{
  if(m_stop)
    m_drivetrain->Stop();
}


bool CmdDriveStraight::IsFinished() 
{

  //Check timer
  if ((m_timeout>0.0) && m_timer.HasElapsed( units::second_t(m_timeout) ) )
  {
      m_timer.Stop();
      std::cout<<"CmdDriveStraight: Timeout"<<std::endl;
      return true;
  }

  //Check Distance
  // sqrt( (x2-x1)^2 + (y2-y1)^2 )
  if( m_distance > 0.0 )
  {
    float delta_x  = m_drivetrain->GetOdometryX() - m_initial_x;
    float delta_y  = m_drivetrain->GetOdometryY() - m_initial_y;
    float distance = sqrtf( delta_x*delta_x + delta_y*delta_y );

    if( distance >= m_distance )
    {
      std::cout<<"CmdDriveStraight: Distance"<<std::endl;

      //DEBUG
      float curr_x = m_drivetrain->GetOdometryX();
      float curr_y = m_drivetrain->GetOdometryY();
      std::cout<<"    ("<<curr_x<<","<<curr_y<<") : "<<distance<<std::endl;

      return true;
    }
  }

  return false;
}
