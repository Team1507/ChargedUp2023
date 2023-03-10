#include "commands/CmdDriveToAprilTag.h"
#include <iostream>
#include <math.h>

#define YAW_ERROR 2.0
#define X_BUFFER_DISTANCE 26.25
#define ERROR_TOLORANCE 1.0

#define DEG2RAD(deg) ( deg*M_PI/180.0)
#define RAD2DEG(rad) ( rad*180.0/M_PI)

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
    // m_preformedCalc = false;

    // m_turnComplete = false;
    // m_sideMoveComplete = false;
    // m_fwrdMovementComplete = false;
    m_count = 0;
    m_delay = 0;
}


void CmdDriveToAprilTag::Execute() 
{
  m_tagAngle = m_Camera->TargetGetYaw();
  m_tagDistance = m_Camera->TargetGetDistance()*39.37;//inches

  // float xDistanceTotal   = m_tagDistance * cosf(DEG2RAD(m_tagAngle));//
  // float xDistanceFromTag = xDistanceTotal - X_BUFFER_DISTANCE;//
  // float yDistanceTotal   = m_tagDistance * sinf(DEG2RAD(m_tagAngle));
  // float e                = sqrt(pow(xDistanceFromTag,2)+pow(yDistanceTotal,2));

  // // float yDistanceTotal   = sqrt(pow(m_tagDistance,2) - pow(xDistanceTotal,2));//B
  // // float angle2Target     = RAD2DEG(atan2(yDistanceTotal, xDistanceFromTag));
  // std::cout<<"m_tagAngle "<<m_tagAngle<<" m_tagDistance "<<m_tagDistance<<std::endl;
  // std::cout<<"xDistanceTotal "<<xDistanceTotal<<" xDistanceFromTag "<<xDistanceFromTag<<" yDistanceTotal "<<yDistanceTotal<<" e "<<e<<std::endl;
  const float MAX_POWER = m_power;
  const float MIN_POWER = 0.0625;       //Must be > MINIMUM_NEEDED_POWER in drivetrain
  const float TURN_Kp   = 0.005;
  m_count++;

  if(m_Camera->IsTarget())
  {
    switch(m_currState)
    {
      // //Turning DriveTrain to 0 for Calculation
      case TURN_TO_ZERO:
      {

        const float targetAngle = 90.0;

        float m_currAngle = m_drivetrain->GetGyroYaw();

        float errorAngle  = m_currAngle - targetAngle;

        float turn_power  = fabs( errorAngle * TURN_Kp ) + MIN_POWER;

        if( turn_power > MAX_POWER ) turn_power = MAX_POWER;
        if( turn_power < MIN_POWER ) turn_power = MIN_POWER;

        if( errorAngle > 0)
          m_drivetrain->RobotcentricDrive(0,0, turn_power); // Error Positive, turn Left
        else
          m_drivetrain->RobotcentricDrive(0,0, -turn_power); // Error Negative, Turn Right

        if(  fabs(errorAngle) < .5 )
        {
          m_drivetrain->RobotcentricDrive(0,0,0);
          m_currState = MOVE_TO_YAW_ZERO;
          std::cout<<"turn move complete"<<std::endl;
        }
      }
      break;
      //End of DriveTrain to 0 for Calculation
      case MOVE_TO_YAW_ZERO:
      {
        m_tagAngle = m_Camera->TargetGetYaw();
        if(m_tagAngle > ERROR_TOLORANCE)
        {
          m_drivetrain->RobotcentricDrive(-m_power, 0, 0);
        }
        else if(m_tagAngle < -ERROR_TOLORANCE)
        {
          m_drivetrain->RobotcentricDrive(m_power, 0, 0);
        }

        if((m_tagAngle+1) < ERROR_TOLORANCE && (m_tagAngle+1) > -ERROR_TOLORANCE)
        {
          m_drivetrain->RobotcentricDrive(0,0,0);
          m_currState = FINSHED;
          std::cout<<"Side move complete"<<std::endl;
          // std::cout<<m_delay<<std::endl;
          
        }    
      } 
        break;

  //     case MOVE_TOWARDS_TARGET:
  //     {
  //         float m_distance = m_Camera->TargetGetDistance();
  //         if(m_distance > X_BUFFER_DISTANCE)
  //         {
  //           m_drivetrain->RobotcentricDrive(0,m_power,0);
  //         }
  //         else
  //         {
  //           m_drivetrain->RobotcentricDrive(0,0,0);
  //           std::cout<<"fwd move complete"<<std::endl;
  //           m_currState = FINSHED;
  //         }   
  //     }
  //         break;
  //   }
  }
    
  // case MOVE_TOWARDS_TARGET:
  //   {
  //     if(!m_preformedCalc)
  //     {
  //       float x_power = m_power * (xDistanceFromTag/e);
  //       float y_power = -m_power * yDistanceTotal/e;//No touch
  //       //float x_power = m_power * sinf(DEG2RAD(angle2Target));
  //       //float y_power = m_power * cosf(DEG2RAD(angle2Target));

  //       std::cout<<"x_power: "<<x_power<<" y_power: "<<y_power<<std::endl;

  //       m_drivetrain->RobotcentricDrive(y_power, x_power, 0);
  //       m_preformedCalc = true;
  //     }
  //     //else if(xDistanceFromTag<ERROR_TOLORANCE)
  //     else if((fabs(m_tagAngle) < ERROR_TOLORANCE))// && (xDistanceFromTag<ERROR_TOLORANCE))
  //     {
  //       m_currState = FINSHED;
  //       m_drivetrain->RobotcentricDrive(0.0,0.0,0.0); 
  //       std::cout<<"Moved to target complete"<<std::endl;
  //     }
  //     std::cout<<"x Distance: "<<xDistanceFromTag<<std::endl;
  //   }
  // }    
  
  // //********************************TURN TO GYRO******************************
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
      
  }    
  
}


void CmdDriveToAprilTag::End(bool interrupted) {}
    

bool CmdDriveToAprilTag::IsFinished() 
{
  if(m_currState == FINSHED)
  {
    std::cout<<"Finished Itself"<<std::endl;
    return true;
  }
  else if(m_count > 250)//5 seconds
  {
    std::cout<<"Timeout"<<std::endl;
    return true;
  }
  else if(!m_Camera->IsTarget())
  {
    std::cout<<"Lost Target"<<std::endl;
    return true;
  }
  else
  {
    return false;
  }
  
}
