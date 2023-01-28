#include "commands/CmdToperatorDefault.h"
#include "Constants.h"

CmdToperatorDefault::CmdToperatorDefault(Toperator *toperator, frc::XboxController *topDriver, Claw *claw, Arm *arm, Pouch *pouch, DriverFeedback *driverfeedback) 
{
  AddRequirements(toperator);
  m_toperator = toperator;
  m_topDriver = topDriver;
  m_claw = claw;
  m_arm = arm;
  m_pouch = pouch;
  m_driverFeedback = driverfeedback;
}

// Called when the command is initially scheduled.
void CmdToperatorDefault::Initialize() 
{
  m_isIntaking = false;
}

// Called repeatedly when this Command is scheduled to run
void CmdToperatorDefault::Execute() 
{
  //**********************BUTTON MAPPINGS**********************
    bool  YButtonPressed   = m_topDriver->GetYButton();
    bool  AButtonPressed   = m_topDriver->GetAButton();
    bool  XButtonPressed   = m_topDriver->GetXButtonPressed();
    bool  BButtonPressed   = m_topDriver->GetBButtonPressed();

    bool  ArmExtention     = m_topDriver->GetLeftY() > .9;
    bool  ArmRetract       = m_topDriver->GetLeftY() < -.9;

    bool  InnerIntake      = m_topDriver->GetLeftBumper();
    bool  OuterIntake      = m_topDriver->GetRightBumper();

    bool  ClawOutake       = m_topDriver->GetRightTriggerAxis() > .9;
    bool  ClawIntake       = m_topDriver->GetLeftTriggerAxis() < -.9;

    bool  ReadyPosition    = m_topDriver->GetBackButtonPressed();
    bool  CloseOuterIntake = m_topDriver->GetStartButton();

    float WristManual      = m_topDriver->GetRightY();
    float TurretManual     = m_topDriver->GetRightX();

    int   DpadState        = m_topDriver->GetPOV();
  //************************************************************
  static bool isDpadCenter = false;
  if(DpadState == -1)
  {
    isDpadCenter = true;
  }
  if(isDpadCenter)
  {
    if(YButtonPressed)
    {
      switch(DpadState)
      {
        case 0 : // up
          break;
        case 90: // right
          break;
        case 180: // down
          break;
        case 270: // left
          break;
      }
    }
    else if(AButtonPressed)
    {
      switch(DpadState)
      {
        case 0 : // up
          break;
        case 90: // right
          break;
        case 180: // down
          break;
        case 270: // left
          break;
      }
    }
    else
    {
      switch(DpadState)
      {
        case 0 : // up
          break;
        case 90: // right
          break;
        case 180: // down
          break;
        case 270: // left
          break;
      }
    }
  }
  if(ClawIntake)
  {
    m_claw->ClawSetPower(.3);
    m_isIntaking = true;
  }
  else if(!ClawIntake && m_isIntaking)
  {
    m_claw->ClawSetPower(0);
    m_isIntaking = false;
  }

    
}

// Called once the command ends or is interrupted.
void CmdToperatorDefault::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdToperatorDefault::IsFinished() 
{
  return false;
}
