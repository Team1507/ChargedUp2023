// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "commands/CmdDriverFeedbackDefault.h"
#include <frc2/command/button/JoystickButton.h>


#include "commands/ExampleCommand.h"
#include "commands/CmdClawDefault.h"
#include "commands/CmdArmDefault.h"
#include "commands/CmdPouchDefault.h"
#include "commands/CmdToperatorDefault.h"
#include "commands/CmdDriveWithGamepad.h"

#include "commands/CmdCalibrateSwerveEncoders.h"
#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveTypeToggle.h"
#include "commands/CmdDriveForceSteerAngle.h"
#include "commands/GrpTest1.h"
#include "commands/GrpTest2.h"
#include "commands/CmdResetGyro.h"

#include "commands/CmdDriveTurnTo90.h"
#include "commands/CmdGyroSetAngleOffset.h"
#include "commands/CmdDriveToAprilTag.h"
#include "commands/CmdAutoBalance.h"


RobotContainer::RobotContainer() 
{

  //**************************** Subsystem Defaults****************************************
  m_drivetrain.SetDefaultCommand(CmdDriveWithGamepad(&m_drivetrain, &m_botDriver));
  m_claw.SetDefaultCommand(CmdClawDefault(&m_claw));
  m_arm.SetDefaultCommand(CmdArmDefault(&m_arm));
  m_pouch.SetDefaultCommand(CmdPouchDefault(&m_pouch));
  m_driverfeedback.SetDefaultCommand(CmdDriverFeedbackDefault(&m_driverfeedback, &m_topDriver, &m_claw));

#ifndef DRIVETRAIN_ONLY
  m_toperator.SetDefaultCommand(CmdToperatorDefault(&m_toperator, &m_topDriver, &m_claw, &m_arm, &m_pouch,  &m_driverfeedback));

//&m_camera,
  //*************************************Auto**********************************************

  m_chooser.SetDefaultOption("Auto Do Nothing", &m_autoDoNothing);
  m_chooser.AddOption("AutoChargeStation", &m_autoChargeStation);
  //m_chooser.AddOption("AutoTwoPieceLeft", &m_autoTwoPieceLeft);
  //m_chooser.AddOption("AutoTwoPieceRight", &m_autoTwoPieceRight);
  //m_chooser.AddOption("AutoScoreLink", &m_autoScoreLink);
#endif
  //m_chooser.AddOption("Auto Shoot Two Ball", &m_autoTwoBall);

  frc::SmartDashboard::PutData("Auto",&m_chooser);

  //********************************Smart Dashboard Buttons**************************************
#ifndef DRIVETRAIN_ONLY
  frc::SmartDashboard::PutData( "GrpTest1", new GrpTest1(&m_drivetrain,&m_arm,&m_claw,&m_pouch));
  frc::SmartDashboard::PutData( "GrpTest2", new GrpTest2(&m_drivetrain,&m_arm,&m_claw,&m_pouch));
#endif
//&m_camera,
//&m_camera,




  frc::SmartDashboard::PutData( "CmdDriveClearAll",   new CmdDriveClearAll(&m_drivetrain));
  frc::SmartDashboard::PutData( "CmdDriveTypeToggle", new CmdDriveTypeToggle(&m_drivetrain));
  frc::SmartDashboard::PutData( "CmdGyroSetAngleOffset", new CmdGyroSetAngleOffset(&m_drivetrain,90.0));
  frc::SmartDashboard::PutData( "CmdAutoBalance", new CmdAutoBalance(&m_drivetrain));

  frc::SmartDashboard::PutData( "CmdDriveTurnTo90", new CmdDriveTurnTo90(&m_drivetrain,0.3));


  //Smartdashboard SwerveDrive test/calibration buttons
  frc::SmartDashboard::PutData( "SteerAngle=0",       new CmdDriveForceSteerAngle(&m_drivetrain,0.0));
  frc::SmartDashboard::PutData( "SteerAngle=90",      new CmdDriveForceSteerAngle(&m_drivetrain,90.0));
  frc::SmartDashboard::PutData( "CmdCalSwerveEnc_1",  new CmdCalibrateSwerveEncoders(&m_drivetrain,1));
  frc::SmartDashboard::PutData( "CmdCalSwerveEnc_2",  new CmdCalibrateSwerveEncoders(&m_drivetrain,2));


  


  // Configure the button bindings
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() 
{
  m_botDriver_START.OnTrue(new CmdResetGyro(&m_drivetrain));
  m_botDriver_Y.WhileTrue(new CmdDriveTurnTo90(&m_drivetrain, .3));
  m_botDriver_A.WhenPressed(new CmdDriveToAprilTag(&m_drivetrain, &m_camera,0.15));
}

frc2::Command* RobotContainer::GetAutonomousCommand() 
{
  return m_chooser.GetSelected();
  }
