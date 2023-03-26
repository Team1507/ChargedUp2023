#include "commands/CmdAutoBalance.h"
#include "Robot.h"
#include "frc2/command/WaitCommand.h"
#include <iostream>
#define ERROR 2
#define DELAY 52 //WORKED AT FLR
#define CHECK_DELAY 50

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
  m_speed = .3;
  m_timer.Reset();
  m_offDelayCount = DELAY;
  m_checkDelay = CHECK_DELAY;
  m_speedDelayCount = 20;
  m_rev = false;
  m_initial = false;    
  m_check = false;
}

void CmdAutoBalance::Execute() 
{
  
  float currRoll  = m_drivetrain->GetGyroRoll();
  float currPitch = m_drivetrain->GetGyroPitch();

  if(m_drivetrain->GetGyroRoll() > 0 + ERROR && !m_rev)
  {
    m_drivetrain->RobotcentricDrive( 0, -m_speed ,0.0);   
  }

  else if(m_drivetrain->GetGyroRoll() < 0 - ERROR && !m_rev)
  {
    m_drivetrain->RobotcentricDrive( 0, m_speed ,0.0);   
  }

  else if(m_drivetrain->GetGyroPitch() > 0 + ERROR && !m_rev)
  {
    m_drivetrain->RobotcentricDrive(-m_speed, 0, 0.0);
  }

  else if(m_drivetrain->GetGyroPitch() < 0 - ERROR && !m_rev)
  {
    m_drivetrain->RobotcentricDrive(m_speed, 0, 0.0);
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
    m_speed = .13;
  }

  //std::cout<<m_drivetrain->GetGyroRoll()<<std::endl;

  if(prevRoll > 0 && currRoll < 0 )
  {
    m_drivetrain->RobotcentricDrive(0 ,.15 ,0.0);
    m_rev = true;
  }

  else if(prevRoll < 0 && currRoll > 0)
  {
    m_drivetrain->RobotcentricDrive(0,-.15,0.0);
    m_rev = true;
  }

  else if(prevPitch > 0 && currPitch < 0)
  {
    m_drivetrain->RobotcentricDrive(.15, 0  ,0.0);
    m_rev = true;
  }
  
  else if(prevPitch < 0 && currPitch > 0)
  {
    m_drivetrain->RobotcentricDrive(-.15, 0  ,0.0);
    m_rev = true;
  }


  if(m_rev)
  {
    m_offDelayCount--;
    if(m_offDelayCount <= 0)
    {
        m_drivetrain->RobotcentricDrive(0 ,0 ,0.0);
        m_check = true;
    }
  }

  if(m_check)
  {
    m_checkDelay--;
  }
    
  prevRoll = currRoll;
}

void CmdAutoBalance::End(bool interrupted) {}

bool CmdAutoBalance::IsFinished() 
{
    //float currRoll  = m_drivetrain->GetGyroRoll();
    if(m_rev && (m_offDelayCount <= 0)) //&& (fabs(currRoll) < .5 ))
    {
        m_drivetrain->ForcePark();
        m_drivetrain->ForcePark();
        return true;
    }
    // else if(m_rev && (m_offDelayCount < 0) && !(fabs(currRoll) < .5 ) && (m_checkDelay < 0))
    // {
    //   m_offDelayCount = DELAY; 
    //   m_rev = false;
    //   m_check = false;
    //   m_checkDelay = CHECK_DELAY;
    //   return false;
    // }
    else return false;
      
    
    
}

