#include "commands/CmdToperatorDefault.h"
#include "Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

#define POUCH_TURRET_LIMIT 5
//Camera *camera,

CmdToperatorDefault::CmdToperatorDefault(Toperator *toperator, frc::XboxController *topDriver, Claw *claw, Arm *arm, Pouch *pouch,  DriverFeedback *driverfeedback) 
{
  AddRequirements(toperator);
  m_toperator      = toperator;
  m_topDriver      = topDriver;
  m_claw           = claw;
  m_arm            = arm;
  m_pouch          = pouch;
  m_driverFeedback = driverfeedback;
  //m_camera         = camera;


  m_isIntaking            = false;
  m_isOuttaking           = false;
  m_isDpadCenter          = false;
  m_isInnerIntaking       = false;
  m_isOuterIntaking       = false;
  m_isOuterIntakeClosed   = false;
  m_isRampActivated       = false;
  m_isTurret              = false;
  m_wristManualOverride   = false;
  m_isOuterIntakeDeployed = false;
  m_wristHome             = false;


  m_scoringHome      = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, Home     );
  m_scoringReady     = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, Ready    );

  m_scoringHighLeft  = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, HighLeft );
  m_scoringHighShelf = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, HighShelf);
  m_scoringHighRight = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, HighRight);

  m_scoringMidLeft   = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, MidLeft  );
  m_scoringMidShelf  = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, MidShelf );
  m_scoringMidRight  = new GrpScoringSetPosition(m_arm, m_claw,m_pouch, MidRight );

  m_scoringHighCone  = new GrpScoringStraightOn(m_arm, m_claw, m_pouch, HighCone);
  m_scoringHighCube  = new GrpScoringStraightOn(m_arm, m_claw, m_pouch, HighCube);
  m_scoringMidCone   = new GrpScoringStraightOn(m_arm, m_claw, m_pouch, MidCone );
  m_scoringMidCube   = new GrpScoringStraightOn(m_arm, m_claw, m_pouch, MidCube );

  m_findHome         = new GrpAllFindHome       (m_arm, m_pouch, m_claw);

  m_returnToPouch    = new GrpReturnToPouch     (m_arm, m_pouch, m_claw);

  m_clawEject        = new CmdClawEject         (m_claw);
}

// Called when the command is initially scheduled.
void CmdToperatorDefault::Initialize() 
{
  frc::SmartDashboard::PutNumber("CONE_INTAKE_POWER", CONE_INTAKE_POWER);
  frc::SmartDashboard::PutNumber("CUBE_INTAKE_POWER", CUBE_INTAKE_POWER);
  std::cout<<"Toperator Default Init"<<std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdToperatorDefault::Execute() 
{
  //**********************BUTTON MAPPINGS**********************
    bool  YButtonPressed   = m_topDriver->GetYButton();
    frc::SmartDashboard::PutBoolean("YButtonPressed",YButtonPressed);
    bool  AButtonPressed   = m_topDriver->GetAButton();
    frc::SmartDashboard::PutBoolean("AButtonPressed",AButtonPressed);
    bool  XButtonPressed   = m_topDriver->GetXButtonPressed();
    frc::SmartDashboard::PutBoolean("XButtonPressed",XButtonPressed);
    bool  BButtonPressed   = m_topDriver->GetBButtonPressed();
    frc::SmartDashboard::PutBoolean("BButtonPressed",BButtonPressed);

    bool  ArmExtention     = m_topDriver->GetLeftY() < -.9;
    bool  ArmRetract       = m_topDriver->GetLeftY() > .9;

    bool  InnerIntake      = m_topDriver->GetRightStickButton();
    frc::SmartDashboard::PutBoolean("Inner Intake",InnerIntake);
    bool  OuterIntakeDeploy   = m_topDriver->GetLeftBumper();
    bool  OuterIntakeRun      = m_topDriver->GetRightBumper();
    frc::SmartDashboard::PutBoolean("Outer Intake",OuterIntakeRun);
    //bool  PouchRamp        = m_topDriver->GetRightStickButton();
    //frc::SmartDashboard::PutBoolean("Pouch Ramp",PouchRamp);


    
    bool  ClawOutake       = m_topDriver->GetRightTriggerAxis() > .8;
    bool  ClawIntake       = m_topDriver->GetLeftTriggerAxis() > .8;

    bool  ReadyPosition    = m_topDriver->GetBackButtonPressed();
    bool  CloseOuterIntake = m_topDriver->GetStartButton();

    float WristManual      = m_topDriver->GetRightY();
    #ifdef TURRET
    float TurretManual     = m_topDriver->GetRightX();
    #endif
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
          //m_scoringHighShelf->Schedule();
          m_isDpadCenter = false;
          std::cout<<"High Shelf"<<std::endl;
          break;
        case 90: // right
          m_scoringHighCone->Schedule();
          m_isDpadCenter = false;
          std::cout<<"High Right"<<std::endl;
          break;
        case 180: // down
          // m_findHome->Schedule();
          // m_driverFeedback->DriverFeedbackLED(COLOR_CLEAR);
          // m_isDpadCenter = false;
          // std::cout<<"Home"<<std::endl;
          break;
        case 270: // left
          m_scoringHighCube->Schedule();
          m_isDpadCenter = false;
          std::cout<<"High Left"<<std::endl;
          break;
      }
    }
    else if(AButtonPressed)
    {
      switch(DpadState)
      {
        case 0 : // up
          //m_scoringMidShelf->Schedule();
          m_isDpadCenter = false;
          std::cout<<"Mid Shelf"<<std::endl;
          break;
        case 90: // right
          m_scoringMidCone->Schedule();
          m_isDpadCenter = false;
          std::cout<<"Mid Right"<<std::endl;
          break;
        case 180: // down
          // m_findHome->Schedule();
          // m_driverFeedback->DriverFeedbackLED(COLOR_CLEAR);
          // m_isDpadCenter = false;
          break;
        case 270: // left
          m_scoringMidCube->Schedule();
          m_isDpadCenter = false;
          std::cout<<"Mid Left"<<std::endl;
          break;
      }
    }
    else
    {
      switch(DpadState)
      {
        case 0 : // up
          //m_camera->PipelineSetIndex(CameraIndex::AprilTag);
          m_isDpadCenter = false;
          break;
        case 90: // right
          //m_camera->PipelineSetIndex(CameraIndex::Cone);
          m_claw->ClawSetIntakePower( frc::SmartDashboard::GetNumber("CONE_INTAKE_POWER", CONE_INTAKE_POWER));
          m_claw->WristSetReadyPosition(13);
          m_driverFeedback->DriverFeedbackLED(COLOR_YELLOW);
          m_isDpadCenter = false;
          std::cout<<"Set Cone"<<std::endl;
          break;
        case 180: // down

          if( m_arm->ElevationHomeLimitSwitch() )
          {
            //On Limit switch - ignore commands
            std::cout<<"Find Home ignored - on limit switch!!"<<std::endl;
          }
          else
          {
            //OK to schedule FindHome commands
            m_arm->ExtensionSetPosition(false),
            m_returnToPouch->Schedule();
            m_driverFeedback->DriverFeedbackLED(COLOR_CLEAR);
            std::cout<<"Find Pouch"<<std::endl;
          }

          m_isDpadCenter = false;

          break;
        case 270: // left
          //m_camera->PipelineSetIndex(CameraIndex::Cube);
          m_claw->ClawSetIntakePower(  frc::SmartDashboard::GetNumber("CUBE_INTAKE_POWER", CUBE_INTAKE_POWER));
          m_claw->WristSetReadyPosition(11);
          //m_claw->ClawSetOuttakePower();
          m_driverFeedback->DriverFeedbackLED(COLOR_PURPLE);
          m_isDpadCenter = false;
          std::cout<<"Set Cube"<<std::endl;
          break;
      }
    }
  }
  if(!YButtonPressed && !AButtonPressed && ReadyPosition)
  {
    m_claw->WristHoldPosition(2);
    m_arm->ElevationArmSetPosition(ArmLevel::Low);
  }
  if(YButtonPressed && ReadyPosition)
  {
    m_claw->WristHoldPosition(2);
    m_arm->ElevationArmSetPosition(ArmLevel::Mid);
  }
  if(AButtonPressed && ReadyPosition)
  {
    m_claw->WristHoldPosition(2.0);
    m_claw->ClawSetOuttakePower(-.8);
    m_isLowShot = true;
  }
  //******************CLAW*******************
  if(ClawIntake && !m_isIntaking)
  {
    m_claw->ClawSetManualOverride(true);
    m_isIntaking = true;
  }
  else if(!ClawIntake && m_isIntaking)
  {
    m_claw->ClawSetManualOverride(false);
    m_isIntaking = false;
  }

  if(ClawOutake && !m_isOuttaking && !m_isLowShot)
  {
    m_clawEject->Schedule();
    m_isOuttaking = true;
  }
  else if(ClawOutake && !m_isOuttaking && m_isLowShot)
  {
    m_pouch->SetRampPosition(true);
    m_clawEject->Schedule();
    m_isOuttaking = true;
    m_isLowShot = false;
  }
  else if(!ClawOutake && m_isOuttaking)
  {
    m_pouch->SetRampPosition(false);
    m_isOuttaking = false;
  }

  //******************WRIST**********************
  // const float WRIST_DELTA = .7;
  // if(WristManual > .6)
  // {
  //   float wristPosition = m_claw->WristGetPosition();
  //   m_claw->WristHoldPosition(wristPosition - WRIST_DELTA); 
  //   // m_claw->WristSetPower(-.2);
  // }

  // else if(WristManual < -.6)
  // {
  //   float wristPosition = m_claw->WristGetPosition();
  //   m_claw->WristHoldPosition(wristPosition + WRIST_DELTA);
  //   // m_claw->WristSetPower(.2);
  // }
  if(WristManual > .6 && !m_wristManualOverride)
  {
    m_claw->WristSetPower(-.2);
    m_wristManualOverride = true;
  }
  else if(WristManual < -.6 && !m_wristManualOverride)
  {
    m_claw->WristSetPower(.2);
    m_wristManualOverride = true;
  }
  else if((WristManual < .6 && WristManual > -.6) && m_wristManualOverride)
  {
    m_claw->WristSetPower(0.0);
    m_claw->WristHoldPosition(m_claw->WristGetPosition());
    m_wristManualOverride = false;
  }
//***********************ARM LEVEL MANUAL***********************
if(XButtonPressed)
{
  m_claw->WristHoldPosition(2);
  m_arm->ElevationArmSetPosition(ArmLevel::High);
}
else if(BButtonPressed)
{
  m_claw->WristHoldPosition(2);
  m_arm->ElevationArmSetPosition(ArmLevel::Level_Pouch);
}
//*******************ARM EXTENSION MANUAL************************
if(ArmExtention && (armLevel != ArmLevel::Level_Pouch))
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
  //m_pouch->SetRampPosition(true);
  m_isInnerIntaking = true;
  std::cout<<"IntakeEnable"<<std::endl;
}
else if(!InnerIntake && m_isInnerIntaking)
{
  m_pouch->IntakeEnable(false);
  //m_pouch->SetRampPosition(false);
  std::cout<<"IntakeDisable"<<std::endl;
  m_isInnerIntaking = false;
}
if(OuterIntakeDeploy && !m_isOuterIntakeDeployed && !m_isOuterIntaking)
{
  m_pouch->IntakeDeployHalf();
  m_isOuterIntakeDeployed = true;
}
else if(!OuterIntakeDeploy && m_isOuterIntakeDeployed)
{
  m_pouch->IntakeRetractHalf();
  m_isOuterIntakeDeployed = false;
}
if(OuterIntakeRun && !m_isOuterIntaking)
{
  //m_pouch->IntakeDeploy();
  // m_pouch->IntakeEnable(true);
  m_pouch->IntakeDeploy();
  m_pouch->SetRampPosition(true);
  m_pouch->IntakeSetPower(.5, Pouch::WhatIntake::Outer);
  m_claw->WristHoldPosition(m_claw->WristGetReadyPosition());
  m_claw->ClawIntakeEnable(true);
  std::cout<<"Outer Intake on"<<std::endl;

  m_isOuterIntaking = true;
}
else if(!OuterIntakeRun && m_isOuterIntaking)
{
  //m_pouch->IntakeRetract();
  // m_pouch->IntakeEnable(false);
  m_pouch->IntakeRetract();
  m_pouch->SetRampPosition(false);
  m_pouch->IntakeSetPower(0, Pouch::WhatIntake::Outer);
  m_pouch->IntakeRetractHalf();
  std::cout<<"Outer Intake off"<<std::endl;
  m_claw->ClawIntakeEnable(false);

  m_isOuterIntaking = false;
}

// if(m_claw->ReadSensorState() && !m_wristHome)
// {
//   m_claw->WristHoldPosition(0);
//   m_wristHome = true;
// }
// else if(!m_claw->ReadSensorState() && m_wristHome)
// {
//   m_wristHome = false;
// }


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

// if(PouchRamp && !m_isRampActivated)
// {
//   m_pouch->SetRampPosition(true);
//   m_isRampActivated = true;
//   std::cout<<"Pouch Ramp on"<<std::endl;
// }
// else if(!PouchRamp && m_isRampActivated)
// {
//   m_pouch->SetRampPosition(false);
//   m_isRampActivated = false;
//   std::cout<<"Pouch Ramp off"<<std::endl;
// }
  
//***************************TURRET MANUAL*******************

#ifdef TURRET
  if(TurretManual > .9)
  {
    m_arm->TurretSetPower(-.1); // High speed to make up for the large gear ratio on the Neo
    m_isTurret = true;
  }
  else if(TurretManual < -.9)
  {
    m_arm->TurretSetPower(.1); // High speed to make up for the large gear ratio on the Neo
    m_isTurret = true;
  }
  else if (TurretManual < .9 && TurretManual > -.9 && m_isTurret)
  {
    m_arm->TurretSetPower(0);
    m_isTurret = false;
  }
#endif
}

// Called once the command ends or is interrupted.
void CmdToperatorDefault::End(bool interrupted) 
{
  std::cout<<"Toperator Default End"<<std::endl;  
}

// Returns true when the command should end.
bool CmdToperatorDefault::IsFinished() 
{
  return false;
}










