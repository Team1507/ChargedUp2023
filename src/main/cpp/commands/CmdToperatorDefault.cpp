#include "commands/CmdToperatorDefault.h"
#include "Constants.h"

CmdToperatorDefault::CmdToperatorDefault(Toperator *toperator, frc::XboxController *topDriver, Claw *claw, Arm *arm, Pouch *pouch, DriverFeedback *driverfeedback) 
{
  AddRequirements(toperator);
  m_toperator      = toperator;
  m_topDriver      = topDriver;
  m_claw           = claw;
  m_arm            = arm;
  m_pouch          = pouch;
  m_driverFeedback = driverfeedback;


  m_isIntaking          = false;
  m_isOuttaking         = false;
  m_isDpadCenter        = false;
  m_isInnerIntaking     = false;
  m_isOuterIntakeClosed = false;
  m_isRampActivated     = false;


  m_scoringHome      = new GrpScoringSetPosition(m_arm, m_claw, Home     );
  m_scoringReady     = new GrpScoringSetPosition(m_arm, m_claw, Ready    );

  m_scoringHighLeft  = new GrpScoringSetPosition(m_arm, m_claw, HighLeft );
  m_scoringHighShelf = new GrpScoringSetPosition(m_arm, m_claw, HighShelf);
  m_scoringHighRight = new GrpScoringSetPosition(m_arm, m_claw, HighRight);

  m_scoringMidLeft   = new GrpScoringSetPosition(m_arm, m_claw, MidLeft  );
  m_scoringMidShelf  = new GrpScoringSetPosition(m_arm, m_claw, MidShelf );
  m_scoringMidRight  = new GrpScoringSetPosition(m_arm, m_claw, MidRight );
}

// Called when the command is initially scheduled.
void CmdToperatorDefault::Initialize() 
{

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
    bool  PouchRamp        = m_topDriver->GetRightStickButtonPressed();

    bool  ClawOutake       = m_topDriver->GetRightTriggerAxis() > .9;
    bool  ClawIntake       = m_topDriver->GetLeftTriggerAxis() < -.9;

    bool  ReadyPosition    = m_topDriver->GetBackButtonPressed();
    bool  CloseOuterIntake = m_topDriver->GetStartButton();

    float WristManual      = m_topDriver->GetRightY();
    float TurretManual     = m_topDriver->GetRightX();

    int   DpadState        = m_topDriver->GetPOV();
  //************************************************************
  //*******************SCORING POSITIONS************************
  if(DpadState == -1)
  {
    m_isDpadCenter = true;
  }
  if(m_isDpadCenter)
  {
    if(YButtonPressed)
    {
      switch(DpadState)
      {
        case 0 : // up
          m_scoringHighShelf->Schedule();
          m_isDpadCenter = false;
          break;
        case 90: // right
          m_scoringHighRight->Schedule();
          m_isDpadCenter = false;
          break;
        case 180: // down
          m_scoringHome->Schedule();
          m_isDpadCenter = false;
          break;
        case 270: // left
          m_scoringHighLeft->Schedule();
          m_isDpadCenter = false;
          break;
      }
    }
    else if(AButtonPressed)
    {
      switch(DpadState)
      {
        case 0 : // up
          m_scoringMidShelf->Schedule();
          m_isDpadCenter = false;
          break;
        case 90: // right
          m_scoringMidRight->Schedule();
          m_isDpadCenter = false;
          break;
        case 180: // down
          m_scoringHome->Schedule();
          m_isDpadCenter = false;
          break;
        case 270: // left
          m_scoringMidLeft->Schedule();
          m_isDpadCenter = false;
          break;
      }
    }
    else
    {
      switch(DpadState)
      {
        case 0 : // up
          m_isDpadCenter = false;
          break;
        case 90: // right
          m_isDpadCenter = false;
          break;
        case 180: // down
          m_isDpadCenter = false;
          break;
        case 270: // left
          m_isDpadCenter = false;
          break;
      }
    }
  }
  if(ReadyPosition)
  {
    m_scoringReady->Schedule();
  }
  //******************CLAW*******************
  if(ClawIntake && !m_isIntaking)
  {
    m_claw->ClawSetPower(.3);
    m_isIntaking = true;
  }
  else if(!ClawIntake && m_isIntaking)
  {
    m_claw->ClawSetPower(0);
    m_isIntaking = false;
  }

  if(ClawOutake && !m_isOuttaking)
  {
    m_claw->ClawSetPower(.3);
    m_isOuttaking = true;
  }
  if(!ClawOutake && m_isOuttaking)
  {
    m_claw->ClawSetPower(0);
    m_isOuttaking = false;
  }
  //******************WRIST**********************
  const float WRIST_DELTA = 100;
  if(WristManual > .6)
  {
    float wristPosition = m_claw->WristGetPosition();
    m_claw->WristSetPosition(wristPosition + WRIST_DELTA); 
  }

  if(WristManual < -.6)
  {
    float wristPosition = m_claw->WristGetPosition();
    m_claw->WristSetPosition(wristPosition + WRIST_DELTA);
  }
//***********************ARM LEVEL MANUAL***********************
if(XButtonPressed)
{
  m_arm->ElevationArmSetPosition(ArmLevel::High);
}
else if(BButtonPressed)
{
  m_arm->ElevationArmSetPosition(ArmLevel::Level_Pouch);
}
//*******************ARM EXTENSION MANUAL************************
if(ArmExtention)
{
  m_arm->ExtensionSetPosition(true);
}
else if(ArmRetract)
{
  m_arm->ExtensionSetPosition(false);
}
//***********************INTAKES*********************************
if(InnerIntake && !m_isInnerIntaking)
{
  m_pouch->SetIntakePower(.3, Pouch::WhatIntake::Inner);
  m_isInnerIntaking = true;
}
else if(!InnerIntake && m_isInnerIntaking)
  m_pouch->SetIntakePower(0, Pouch::WhatIntake::Inner);
  m_isInnerIntaking = false;

if(OuterIntake && !m_isOuterIntaking)
{
  m_pouch->DeployIntake(Pouch::WhatIntake::Outer);
  m_pouch->SetIntakePower(.3, Pouch::WhatIntake::Outer);
  m_isOuterIntaking = false;
}
else if(!OuterIntake && m_isInnerIntaking)
{
  m_pouch->RetractIntake(Pouch::WhatIntake::Outer);
  m_pouch->SetIntakePower(0, Pouch::WhatIntake::Outer);
  m_isOuterIntaking = true;
}

if(CloseOuterIntake && !m_isOuterIntakeClosed)
{
  m_pouch->CloseOuterIntake();
  m_isOuterIntakeClosed = true;
}
else if (!CloseOuterIntake && m_isOuterIntakeClosed)
{
  m_pouch->OpenOuterIntake();
  m_isOuterIntakeClosed = false;
}

if(PouchRamp && !m_isRampActivated)
{
  m_pouch->SetRampPosition(true);
  m_isRampActivated = true;
}
else if(PouchRamp && m_isRampActivated)
{
  m_pouch->SetRampPosition(false);
  m_isRampActivated = false;
}
  

    
}

// Called once the command ends or is interrupted.
void CmdToperatorDefault::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdToperatorDefault::IsFinished() 
{
  return false;
}
