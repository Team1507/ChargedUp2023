#include "commands/CmdDriveTurnToTarget.h"
#include "Robot.h"

#include <iostream>
#include <math.h>

CmdDriveTurnToTarget::CmdDriveTurnToTarget(Drivetrain *drivetrain, Camera *camera,float power) 
{
  m_power = power;
  m_drivetrain = drivetrain;
  m_camera     = camera;

  AddRequirements({ drivetrain });
}


void CmdDriveTurnToTarget::Initialize() 
{
    m_angle     = m_camera->TargetGetYaw();
    m_calcAngle = m_angle + m_drivetrain->GetGyroAngle();
}


void CmdDriveTurnToTarget::Execute() 
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

void CmdDriveTurnToTarget::End(bool interrupted) 
{
  m_drivetrain->Stop();
}

bool CmdDriveTurnToTarget::IsFinished() 
{
  float delta_angle = m_calcAngle - m_drivetrain->GetGyroAngle();
  if(  abs(delta_angle) < 2.5 )
    return true;
  return false;
}
