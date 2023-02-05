// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveTurn2Angle.h"
#include "Robot.h"

#include <iostream>
#include <math.h>

CmdDriveTurn2Angle::CmdDriveTurn2Angle(Drivetrain *drivetrain, float power, float angle) 
{
  m_power = power;
  m_angle = angle;

  m_drivetrain = drivetrain;

  AddRequirements({drivetrain });
}


void CmdDriveTurn2Angle::Initialize() 
{
  m_calcAngle = m_drivetrain->GetGyroAngle() + m_angle;
}


void CmdDriveTurn2Angle::Execute() 
{

  float const MAX_POWER = m_power;
  float const MIN_POWER = 0.0625;       //Must be > MINIMUM_NEEDED_POWER in drivetrain
  float const TURN_Kp   = 0.005;

  float delta_angle = m_calcAngle - m_drivetrain->GetGyroAngle();

  float turn_power = abs( delta_angle * TURN_Kp ) + MIN_POWER;

  if( turn_power > MAX_POWER ) turn_power = MAX_POWER;
  if( turn_power < MIN_POWER ) turn_power = MIN_POWER;

  if( delta_angle > 0)
    m_drivetrain->RobotcentricDrive(0,0,  -turn_power);
  else
    m_drivetrain->RobotcentricDrive(0,0,   turn_power);


}


void CmdDriveTurn2Angle::End(bool interrupted) 
{
  m_drivetrain->Stop();
}


bool CmdDriveTurn2Angle::IsFinished()
{
  float delta_angle = m_calcAngle - m_drivetrain->GetGyroAngle();
  if(  abs(delta_angle) < 2.5 )
    return true;

  return false;
}
