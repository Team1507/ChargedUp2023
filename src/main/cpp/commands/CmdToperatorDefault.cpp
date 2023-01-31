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


  m_isIntaking       = false;
  m_isOuttaking      = false;
  m_isDpadCenter     = false;


  m_scoringHome      = new GrpScoringSetPosition(m_arm, Home     );
  m_scoringReady     = new GrpScoringSetPosition(m_arm, Ready    );

  m_scoringHighLeft  = new GrpScoringSetPosition(m_arm, HighLeft );
  m_scoringHighShelf = new GrpScoringSetPosition(m_arm, HighShelf);
  m_scoringHighRight = new GrpScoringSetPosition(m_arm, HighRight);

  m_scoringMidLeft   = new GrpScoringSetPosition(m_arm, MidLeft  );
  m_scoringMidShelf  = new GrpScoringSetPosition(m_arm, MidShelf );
  m_scoringMidRight  = new GrpScoringSetPosition(m_arm, MidRight );
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
  

    
}

// Called once the command ends or is interrupted.
void CmdToperatorDefault::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdToperatorDefault::IsFinished() 
{
  return false;
}
