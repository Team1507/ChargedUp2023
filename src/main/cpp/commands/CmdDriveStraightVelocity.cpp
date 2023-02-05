// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveStraightVelocity.h"
#include "Robot.h"

#include <iostream>
#include <math.h>

CmdDriveStraightVelocity::CmdDriveStraightVelocity(Drivetrain *drivetrain, float speed, float heading, float distance, bool ramp, bool stop, float timeout)
{

  // ** ROBOT CENTRIC **
  // Heading is referenced to the front of the robot
  //   Heading is the direction the robot is moving with respect to the front of the robot

  m_speed    = speed;
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


void CmdDriveStraightVelocity::Initialize() 
{

  m_initial_x = m_drivetrain->GetOdometryX();
  m_initial_y = m_drivetrain->GetOdometryY();

  if( m_timeout > 0.0 )
  {
      m_timer.Reset();
      m_timer.Start();
  }

}


void CmdDriveStraightVelocity::Execute() 
{

  float drive_speed = m_speed;
  
  float y_speed = drive_speed * cosf(m_heading);
  float x_speed = drive_speed * sinf(m_heading);

  m_drivetrain->RobotcentricDriveVelocity(y_speed,x_speed,0.0);

}


void CmdDriveStraightVelocity::End(bool interrupted) 
{
  if(m_stop)
    m_drivetrain->Stop();
}


bool CmdDriveStraightVelocity::IsFinished() 
{

  //Check timer
  if ((m_timeout>0.0) && m_timer.HasElapsed( units::second_t(m_timeout) ) )
  {
      m_timer.Stop();
      std::cout<<"CmdDriveStraightVelocity: Timeout"<<std::endl;
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
      std::cout<<"CmdDriveStraightVelocity: Distance"<<std::endl;

      //DEBUG
      float curr_x = m_drivetrain->GetOdometryX();
      float curr_y = m_drivetrain->GetOdometryY();
      std::cout<<"    ("<<curr_x<<","<<curr_y<<") : "<<distance<<std::endl;

      return true;
    }
  }

  return false;
}
