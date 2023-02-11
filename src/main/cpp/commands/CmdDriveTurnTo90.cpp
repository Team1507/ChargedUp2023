#include "commands/CmdDriveTurnTo90.h"

CmdDriveTurnTo90::CmdDriveTurnTo90(Drivetrain *drivetrain, float power, float angle) 
{
  m_power = power;
  m_angle = angle;

  m_drivetrain = drivetrain;

  AddRequirements({drivetrain });
}


void CmdDriveTurnTo90::Initialize() 
{
  m_calcAngle = 90;
}


void CmdDriveTurnTo90::Execute() 
{

  float const MAX_POWER = m_power;
  float const MIN_POWER = 0.0625;       //Must be > MINIMUM_NEEDED_POWER in drivetrain
  float const TURN_Kp   = 0.005;

  float m_currentAngle = m_drivetrain->GetGyroAngle();

  float turn_power = abs(m_currentAngle * TURN_Kp ) + MIN_POWER;

  if( turn_power > MAX_POWER ) turn_power = MAX_POWER;
  if( turn_power < MIN_POWER ) turn_power = MIN_POWER;

  if(m_currentAngle = 90)
    m_drivetrain->RobotcentricDrive(0,0,  -turn_power);
  else
    m_drivetrain->RobotcentricDrive(0,0,   turn_power);


}


void CmdDriveTurnTo90::End(bool interrupted) 
{
  m_drivetrain->Stop();
}


bool CmdDriveTurnTo90::IsFinished()
{
  float m_currentAngle = m_drivetrain->GetGyroAngle();
  if(m_currentAngle < 90.5 && m_currentAngle > 89.5)
    return true;

  return false;
}
