#include "commands/CmdToperatorDefault.h"
#include "Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>

#define POUCH_TURRET_LIMIT 5


CmdToperatorDefault::CmdToperatorDefault(Toperator *toperator, frc::XboxController *topDriver, Claw *claw, Arm *arm, Pouch *pouch, Camera *camera, DriverFeedback *driverfeedback) 
{
  AddRequirements(toperator);
  m_toperator      = toperator;
  m_topDriver      = topDriver;
  m_claw           = claw;
  m_arm            = arm;
  m_pouch          = pouch;
  m_driverFeedback = driverfeedback;
  m_camera         = camera;


  m_isIntaking          = false;
  m_isOuttaking         = false;
  m_isDpadCenter        = false;
  m_isInnerIntaking     = false;
  m_isOuterIntakeClosed = false;
  m_isRampActivated     = false;
  m_isTurret            = false;


  m_scoringHome      = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, Home     );
  m_scoringReady     = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, Ready    );

  m_scoringHighLeft  = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, HighLeft );
  m_scoringHighShelf = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, HighShelf);
  m_scoringHighRight = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, HighRight);

  m_scoringMidLeft   = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, MidLeft  );
  m_scoringMidShelf  = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, MidShelf );
  m_scoringMidRight  = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, MidRight );

  m_findHome         = new GrpAllFindHome       (m_arm, m_pouch, m_claw);

  m_clawEject        = new CmdClawEject(m_claw);
}

// Called when the command is initially scheduled.
void CmdToperatorDefault::Initialize() 
{
  frc::SmartDashboard::PutNumber("CONE_INTAKE_POWER", CONE_INTAKE_POWER);
  frc::SmartDashboard::PutNumber("CUBE_INTAKE_POWER", CUBE_INTAKE_POWER);
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
    bool  PouchRamp        = m_topDriver->GetRightStickButton();

    bool  ClawOutake       = m_topDriver->GetRightTriggerAxis() > .9;
    bool  ClawIntake       = m_topDriver->GetLeftTriggerAxis() < -.9;

    bool  ReadyPosition    = m_topDriver->GetBackButtonPressed();
    bool  CloseOuterIntake = m_topDriver->GetStartButton();

    float WristManual      = m_topDriver->GetRightY();
    float TurretManual     = m_topDriver->GetRightX();

    int   DpadState        = m_topDriver->GetPOV();

    ArmLevel armLevel = m_arm->ElevationArmGetPosition();

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
          m_findHome->Schedule();
          m_driverFeedback->DriverFeedbackLED(COLOR_CLEAR);
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
          m_findHome->Schedule();
          m_driverFeedback->DriverFeedbackLED(COLOR_CLEAR);
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
          m_camera->PipelineSetIndex(CameraIndex::AprilTag);
          m_isDpadCenter = false;
          break;
        case 90: // right
          m_camera->PipelineSetIndex(CameraIndex::Cone);
          m_claw->ClawSetIntakePower( frc::SmartDashboard::GetNumber("CONE_INTAKE_POWER", CONE_INTAKE_POWER));
          m_driverFeedback->DriverFeedbackLED(COLOR_YELLOW);
          m_isDpadCenter = false;
          break;
        case 180: // down
          m_findHome->Schedule();
          m_driverFeedback->DriverFeedbackLED(COLOR_CLEAR);
          m_isDpadCenter = false;
          break;
        case 270: // left
          m_camera->PipelineSetIndex(CameraIndex::Cube);
          m_claw->ClawSetIntakePower(  frc::SmartDashboard::GetNumber("CUBE_INTAKE_POWER", CUBE_INTAKE_POWER));
          m_driverFeedback->DriverFeedbackLED(COLOR_PURPLE);
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
    m_claw->ClawIntakeEnable(true);
    m_isIntaking = true;
  }
  else if(!ClawIntake && m_isIntaking)
  {
    m_claw->ClawIntakeEnable(false);
    m_isIntaking = false;
  }

  if(ClawOutake && !m_isOuttaking)
  {
    m_clawEject->Schedule();
    m_isOuttaking = true;
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
    m_claw->WristSetPosition(wristPosition - WRIST_DELTA);
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
if(ArmExtention && armLevel == ArmLevel::Level_Pouch)
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
  m_pouch->IntakeEnable(true);
  m_pouch->SetRampPosition(true);
  m_isInnerIntaking = true;
}
else if(!InnerIntake && m_isInnerIntaking)
{
  m_pouch->IntakeEnable(false);
  m_pouch->SetRampPosition(false);
  m_isInnerIntaking = false;
}
if(OuterIntake && !m_isOuterIntaking)
{
  m_pouch->IntakeDeploy();
  m_pouch->SetRampPosition(true);
  m_pouch->IntakeSetPower(.3, Pouch::WhatIntake::Outer);
  m_isOuterIntaking = true;
}
else if(!OuterIntake && m_isInnerIntaking)
{
  m_pouch->IntakeRetract();
  m_pouch->SetRampPosition(false);
  m_pouch->IntakeSetPower(0, Pouch::WhatIntake::Outer);
  m_isOuterIntaking = false;
}


 if(CloseOuterIntake && !m_isOuterIntakeClosed && m_isOuterIntaking)
 {
   m_pouch->OuterIntakeClose();
   m_isOuterIntakeClosed = true;
 }
 else if (!CloseOuterIntake && m_isOuterIntakeClosed)
 {
   m_pouch->OuterIntakeOpen();
   m_isOuterIntakeClosed = false;
 }

if(PouchRamp && !m_isRampActivated)
{
  m_pouch->SetRampPosition(true);
  m_isRampActivated = true;
}
else if(!PouchRamp && m_isRampActivated)
{
  m_pouch->SetRampPosition(false);
  m_isRampActivated = false;
}
  
//***************************TURRET MANUAL*******************


if(TurretManual > .5)
{
  m_arm->TurretSetPower(.9); // High speed to make up for the large gear ratio on the Neo
  m_isTurret = true;
}
else if(TurretManual < -.5)
{
  m_arm->TurretSetPower(-.9); // High speed to make up for the large gear ratio on the Neo
  m_isTurret = true;
}
else if (TurretManual < .5 && TurretManual > -.5 && m_isTurret)
{
  m_arm->TurretSetPower(0);
  m_isTurret = false;
}

}

// Called once the command ends or is interrupted.
void CmdToperatorDefault::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdToperatorDefault::IsFinished() 
{
  return false;
}










