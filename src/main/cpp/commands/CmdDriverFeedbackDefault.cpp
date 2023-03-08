// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriverFeedbackDefault.h"

CmdDriverFeedbackDefault::CmdDriverFeedbackDefault(DriverFeedback *driverfeedback, frc::XboxController *xboxcontroller, Claw *claw) 
{
  AddRequirements(driverfeedback);
  // Use addRequirements() here to declare subsystem dependencies.
  m_driverfeedback   =driverfeedback;
  m_xboxcontroller   =xboxcontroller;
  m_claw             =claw          ;
  m_isPieceCollected = false        ;
  m_delay = 3000;
}

// Called when the command is initially scheduled.
void CmdDriverFeedbackDefault::Initialize() 
{
  
}

// Called repeatedly when this Command is scheduled to run
void CmdDriverFeedbackDefault::Execute() 
{
  bool XButton = m_xboxcontroller -> GetXButton();
  if(XButton == true)
  {
    // m_driverfeedback->Rumble(1.0);
    m_driverfeedback->UnderGlow(1,1,0);
  }

  else
  {
    m_driverfeedback->Rumble(0.0);
    m_driverfeedback->UnderGlow(0,0,1);
  }

  

  if(m_claw->ReadSensorState() == true && m_delay > 0)
  {
    m_driverfeedback->Rumble(1.0);
    m_delay--;
  }

  else if(m_delay < 0)
  {
    m_driverfeedback->Rumble(0.0);
  }
  else if(m_delay < 0 && m_claw->ReadSensorState() == false)
  {
    m_delay = 3000;
  }
} 

// Called once the command ends or is interrupted.
void CmdDriverFeedbackDefault::End(bool interrupted) 
{
  m_driverfeedback->UnderGlow(0,0,0);
}

// Returns true when the command should end.
bool CmdDriverFeedbackDefault::IsFinished() {
  return false;
}
