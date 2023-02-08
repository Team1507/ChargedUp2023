#include "commands/CmdDriveToAprilTag.h"
#include <iostream>

#define YAW_ERROR 2

const int TURN_TO_ZERO = 1;
const int MOVE_TO_YAW_ZERO  = 2;
const int MOVE_TOWARDS_TARGET  = 3;
const int FINSHED = 4;

CmdDriveToAprilTag::CmdDriveToAprilTag(Drivetrain *drivetrain, Camera *Camera, float power) 
{
  m_power = power;
  m_drivetrain = drivetrain;
  m_Camera = Camera;

  AddRequirements({ drivetrain });
}


void CmdDriveToAprilTag::Initialize() 
{
    
    m_tagAngle = m_Camera->TargetGetYaw();
    m_currState = TURN_TO_ZERO;
    // m_turnComplete = false;
    // m_sideMoveComplete = false;
    // m_fwrdMovementComplete = false;
    m_delay = 500;
}


void CmdDriveToAprilTag::Execute() 
{
  const float MAX_POWER = m_power;
  const float MIN_POWER = 0.0625;       //Must be > MINIMUM_NEEDED_POWER in drivetrain
  const float TURN_Kp   = 0.005;

        

  if(m_Camera->IsTarget())
  {
    switch(m_currState)
    {
      case TURN_TO_ZERO:
      {
        float m_currAngle = m_drivetrain->GetGyroYaw();

        float turn_power = abs( m_currAngle * TURN_Kp ) + MIN_POWER;

        if( turn_power > MAX_POWER ) turn_power = MAX_POWER;
        if( turn_power < MIN_POWER ) turn_power = MIN_POWER;

        if( m_currAngle > 0)
          m_drivetrain->RobotcentricDrive(0,0,  turn_power);
        else
          m_drivetrain->RobotcentricDrive(0,0,   -turn_power);

        if(  abs(m_currAngle) < .5 )
        {
          m_drivetrain->RobotcentricDrive(0,0,0);
          m_currState = MOVE_TO_YAW_ZERO;
          std::cout<<"turn move complete"<<std::endl;
        }
      }
        break;

      case MOVE_TO_YAW_ZERO:
      {
        m_tagAngle = m_Camera->TargetGetYaw();
        if(m_tagAngle > 0)
        {
          m_drivetrain->RobotcentricDrive(-m_power, 0, 0);
        }
        else if(m_tagAngle < 0)
        {
          m_drivetrain->RobotcentricDrive(m_power, 0, 0);
        }
        if(m_tagAngle > -2 && m_tagAngle < 2 && m_power > .1)
        {
          m_power = .1;
        }
        if(m_tagAngle < 0 + YAW_ERROR && m_tagAngle > 0 - YAW_ERROR)
        {
          m_drivetrain->RobotcentricDrive(0,0,0);
          m_currState = MOVE_TOWARDS_TARGET;
          std::cout<<"Side move complete"<<std::endl;
          std::cout<<m_delay<<std::endl;
          
        }    
      } 
        break;

      case MOVE_TOWARDS_TARGET:
      {
          float m_distance = m_Camera->TargetGetDistance();
          if(m_distance > .53)
          {
            m_drivetrain->RobotcentricDrive(0,m_power,0);
          }
          else
          {
            m_drivetrain->RobotcentricDrive(0,0,0);
            std::cout<<"fwd move complete"<<std::endl;
            m_currState = FINSHED;
          }   
      }
          break;
    }
    
  //********************************TURN TO GYRO******************************
  //   if(!m_turnComplete)
  //   {
  //     float const MAX_POWER = m_power;
  //     float const MIN_POWER = 0.0625;       //Must be > MINIMUM_NEEDED_POWER in drivetrain
  //     float const TURN_Kp   = 0.005;

  //     float m_currAngle = m_drivetrain->GetGyroYaw();

  //     float turn_power = abs( m_currAngle * TURN_Kp ) + MIN_POWER;

  //     if( turn_power > MAX_POWER ) turn_power = MAX_POWER;
  //     if( turn_power < MIN_POWER ) turn_power = MIN_POWER;

  //     if( m_currAngle > 0)
  //       m_drivetrain->RobotcentricDrive(0,0,  turn_power);
  //     else
  //       m_drivetrain->RobotcentricDrive(0,0,   -turn_power);

  //     if(  abs(m_currAngle) < .5 )
  //     {
  //       m_drivetrain->RobotcentricDrive(0,0,0);
  //       m_turnComplete = true;
  //       std::cout<<"turn move complete"<<std::endl;
  //     }
  //   }

  //   //**************************MOVE IN LINE WITH APRIL TAG********************
  //  if(m_turnComplete)
  //   {
  //     std::cout<<"ahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<std::endl;
  //     std::cout<<m_tagAngle<<std::endl;
  //     std::cout<<m_power<<std::endl;
  //     m_tagAngle = m_Camera->TargetGetYaw();
  //     if(m_tagAngle > 0 && !m_sideMoveComplete)
  //     {
  //       m_drivetrain->RobotcentricDrive(-m_power, 0, 0);
  //     }
  //     else if(m_tagAngle < 0 && !m_sideMoveComplete)
  //     {
  //       m_drivetrain->RobotcentricDrive(m_power, 0, 0);
  //     }
  //     if(m_tagAngle > -2 && m_tagAngle < 2 && m_power > .1)
  //     {
  //       m_power = .1;
  //     }
  //     if(m_tagAngle < 0 + ERROR && m_tagAngle > 0 - ERROR)
  //     {
  //       m_drivetrain->RobotcentricDrive(0,0,0);
  //       m_sideMoveComplete = true;
  //       m_turnComplete = false;
  //       std::cout<<"Side move complete"<<std::endl;
  //       std::cout<<m_delay<<std::endl;
  //     }
  //   }
  //   //****************************MOVE TOWARDS TARGET***********************
  //   if(m_sideMoveComplete)
  //   {
  //     float m_distance = m_Camera->TargetGetDistance();
  //     if(m_distance > .53)
  //     {
  //       m_drivetrain->RobotcentricDrive(0,m_power,0);
  //     }
  //     else
  //     {
  //       m_drivetrain->RobotcentricDrive(0,0,0);
  //       m_fwrdMovementComplete = true;
  //       std::cout<<"fwd move complete"<<std::endl;
  //     }
  //   }
      
  //   }    
  }
}


void CmdDriveToAprilTag::End(bool interrupted) {}
    

bool CmdDriveToAprilTag::IsFinished() 
{
  if(m_currState == FINSHED)
  {
    return true;
  }
  else
  {
    return false;
  }
  
}
