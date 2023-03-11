// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveStraightGyro.h"
#include "Robot.h"

#include <iostream>
#include <math.h>

CmdDriveStraightGyro::CmdDriveStraightGyro(Drivetrain *drivetrain, float power, float gyroHeading, float gyroYaw, float distance, bool ramp, bool stop, float timeout)
{

  // ** FIELD CENTRIC **
  // Heading and yaw are referenced to the gyro angle 0
  //   Heading is the direction the robot is moving with respect gyro angle 0
  //   Yaw is the direction the robot is facing with respect gyro angle 0
  //   Yaw is direction based on robot at power up because yaw calls the wrong function
  //   Heading is based on offset if applicable
  // Set gyroHeading to direction robot should move
  // Set gyroYaw to yaw robot should maintain during move

  m_power    = power;
  m_heading  = gyroHeading * M_PI/180.0;  //Convert to radians
  m_yaw      = gyroYaw;
  m_distance = distance;
  m_stop     = stop;
  m_timeout  = timeout;
  m_ramp     = ramp;

  m_drivetrain = drivetrain;

  m_initial_x = 0;
  m_initial_y = 0;

  AddRequirements({drivetrain });
}


void CmdDriveStraightGyro::Initialize() 
{

  m_initial_x = m_drivetrain->GetOdometryX();
  m_initial_y = m_drivetrain->GetOdometryY();

  if( m_timeout > 0.0 )
  {
      m_timer.Reset();
      m_timer.Start();
  }

}


void CmdDriveStraightGyro::Execute() 
{

  //-------------------------------------
  //  Rotational correction

  //Min turn power is 0.0625.
  //  Set Kp to reach min turn power at 2 deg error  (Kp = min/error = 0.0625/2  )
  float const TURN_MAX_POWER = 0.2;
  float const TURN_Kp        = 0.03;

  float delta_angle = m_yaw - m_drivetrain->GetGyroAngle();

  float turn_power = abs( delta_angle * TURN_Kp );

  //Limit max drive
  if( turn_power > TURN_MAX_POWER ) turn_power = TURN_MAX_POWER;

  //-------------------------------------
  //  Directional calculations

  float drive_power = m_power;
  
  float y_power = drive_power * cosf(m_heading);
  float x_power = drive_power * sinf(m_heading);



//m_drivetrain->RobotcentricDrive(y_power,x_power,0.0);

  if( delta_angle > 0)
    m_drivetrain->FieldcentricDrive( y_power, x_power, -turn_power);
  else
    m_drivetrain->FieldcentricDrive( y_power, x_power,  turn_power);

}


void CmdDriveStraightGyro::End(bool interrupted) 
{
  if(m_stop)
    m_drivetrain->Stop();
}


bool CmdDriveStraightGyro::IsFinished() 
{

  //Check timer
  if ((m_timeout>0.0) && m_timer.HasElapsed( units::second_t(m_timeout) ) )
  {
      m_timer.Stop();
      std::cout<<"CmdDriveStraightGyro: Timeout"<<std::endl;
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
      std::cout<<"CmdDriveStraightGyro: Distance"<<std::endl;

      //DEBUG
      float curr_x = m_drivetrain->GetOdometryX();
      float curr_y = m_drivetrain->GetOdometryY();
      std::cout<<"    ("<<curr_x<<","<<curr_y<<") : "<<distance<<std::endl;

      return true;
    }
  }

  return false;
}
