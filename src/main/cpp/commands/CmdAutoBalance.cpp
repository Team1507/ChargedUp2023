#include "commands/CmdAutoBalance.h"
#include "Robot.h"
#include "frc2/command/WaitCommand.h"
#include <iostream>
#define ERROR 2

float prevRoll = 0;
float prevPitch = 0;
CmdAutoBalance::CmdAutoBalance(Drivetrain *drivetrain) 
{
  m_drivetrain = drivetrain;


  AddRequirements({ drivetrain });
}

void CmdAutoBalance::Initialize() 
{
  prevRoll = 0;
  prevPitch = 0;
  m_speed = .2;
  m_timer.Reset();
  m_offDelayCount = 40;
  m_speedDelayCount = 20;
  m_rev = false;
  m_initial = false;    
}

void CmdAutoBalance::Execute() 
{
  
  float currRoll  = m_drivetrain->GetGyroRoll();
  float currPitch = m_drivetrain->GetGyroPitch();

  if(m_drivetrain->GetGyroRoll() > 0 + ERROR && !m_rev)
  {
    m_drivetrain->RobotcentricDrive( m_speed, 0 ,0.0);   
  }

  else if(m_drivetrain->GetGyroRoll() < 0 - ERROR && !m_rev)
  {
    m_drivetrain->RobotcentricDrive( -m_speed, 0 ,0.0);   
  }

  else if(m_drivetrain->GetGyroPitch() > 0 + ERROR && !m_rev)
  {
    m_drivetrain->RobotcentricDrive(0, m_speed, 0.0);
  }

  else if(m_drivetrain->GetGyroPitch() < 0 - ERROR && !m_rev)
  {
    m_drivetrain->RobotcentricDrive(0,-m_speed, 0.0);
  }


  if(!m_initial)
  {
    m_speedDelayCount--;
    if(m_speedDelayCount <= 0)
    {
      m_initial = true;
    }
  }

  if(m_initial)
  {
    m_speed = .15;
  }

  //std::cout<<m_drivetrain->GetGyroRoll()<<std::endl;

  if(prevRoll > 0 && currRoll < 0 )
  {
    m_drivetrain->RobotcentricDrive(-.25 ,0 ,0.0);
    m_rev = true;
  }

  else if(prevRoll < 0 && currRoll > 0)
  {
    m_drivetrain->RobotcentricDrive(.25 ,0 ,0.0);
    m_rev = true;
  }

  else if(prevPitch > 0 && currPitch < 0)
  {
    m_drivetrain->RobotcentricDrive(0, -.25  ,0.0);
    m_rev = true;
  }
  
  else if(prevPitch < 0 && currPitch > 0)
  {
    m_drivetrain->RobotcentricDrive(0, .25  ,0.0);
    m_rev = true;
  }


  if(m_rev)
  {
    m_offDelayCount--;
    if(m_offDelayCount <= 0)
    {
        m_drivetrain->RobotcentricDrive(0 ,0 ,0.0);
        m_drivetrain->ForcePark();
    }
  }
    
  prevRoll = currRoll;
}

void CmdAutoBalance::End(bool interrupted) {}

bool CmdAutoBalance::IsFinished() 
{

    if(m_rev && (m_offDelayCount < 0))
    {
        return true;
    }
    else
    {
      return false;
    }
      
    
    
}

