#include "commands/CmdDriverFeedbackDefault.h"
#include <iostream>

CmdDriverFeedbackDefault::CmdDriverFeedbackDefault(DriverFeedback *driverfeedback, frc::XboxController *xboxcontroller, Claw *claw) 
{
  AddRequirements(driverfeedback);
  // Use addRequirements() here to declare subsystem dependencies.
  m_driverfeedback   =driverfeedback;
  m_xboxcontroller   =xboxcontroller;
  m_claw             =claw          ;
  m_isPieceCollected = false        ;
  m_isRumble         = false        ;
  m_delay            = 0            ;
}

// Called when the command is initially scheduled.
void CmdDriverFeedbackDefault::Initialize() 
{
    std::cout<<"DriverFeedback Default Init"<<std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdDriverFeedbackDefault::Execute() 
{ 
  //Tyler made me do this == 
  if(m_claw->ReadSensorState() == true  && m_isPieceCollected == false)
  {
    m_driverfeedback->RumbleTop(1.0);
    // m_delay=200;
    m_driverfeedback->DriverFeedbackLED(COLOR_GREEN);
    m_isPieceCollected = true;
    // m_isRumble = true;
  }
  // else if(m_delay<=0 && m_isRumble)
  // {
  //   m_driverfeedback->RumbleBot(0.0);
  //   m_isRumble = false;
  // }
  // else
  // {
  //   m_delay--;
  // }

  if(m_claw->ReadSensorState() == false  && m_isPieceCollected == true)
  {
    m_driverfeedback->RumbleTop(0.0);
    m_driverfeedback->RumbleBot(0.0);
    // m_isRumble=false;

    m_driverfeedback->DriverFeedbackLED(COLOR_CLEAR);
    m_isPieceCollected = false;
  }
  


} 

// Called once the command ends or is interrupted.
void CmdDriverFeedbackDefault::End(bool interrupted) 
{
  std::cout<<"DriverFeedback Default End"<<std::endl;
}

// Returns true when the command should end.
bool CmdDriverFeedbackDefault::IsFinished() {
  return false;
}
