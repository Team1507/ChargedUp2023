// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "commands/CmdDriverFeedbackDefault.h"
#include <frc2/command/button/Trigger.h>

#include "commands/Autos.h"
#include "commands/ExampleCommand.h"
#include "commands/CmdClawDefault.h"
#include "commands/CmdArmDefault.h"
#include "commands/CmdPouchDefault.h"
#include "commands/CmdToperatorDefault.h"
#include "commands/CmdDriveWithGamepad.h"


RobotContainer::RobotContainer() 
{

  //**************************** Subsystem Defaults****************************************
  m_drivetrain.SetDefaultCommand(CmdDriveWithGamepad(& m_drivetrain, &m_botDriver));
  m_claw.SetDefaultCommand(CmdClawDefault(&m_claw));
  m_arm.SetDefaultCommand(CmdArmDefault(&m_arm));
  m_pouch.SetDefaultCommand(CmdPouchDefault(&m_pouch));
  m_toperator.SetDefaultCommand(CmdToperatorDefault(&m_toperator, &m_topDriver, &m_claw, &m_arm, &m_pouch, &m_driverfeedback));
  m_driverfeedback.SetDefaultCommand(CmdDriverFeedbackDefault(&m_driverfeedback, &m_topDriver, &m_claw));

  //*************************************Auto**********************************************

  m_chooser.SetDefaultOption("Auto Do Nothing", &m_autoDoNothing);

  //m_chooser.AddOption("Auto Shoot Two Ball", &m_autoTwoBall);

  frc::SmartDashboard::PutData("Auto",&m_chooser);

  //********************************Smart Dashboard Buttons**************************************




  // Configure the button bindings
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
  // Configure your trigger bindings here

  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  frc2::Trigger([this] {
    return m_subsystem.ExampleCondition();
  }).OnTrue(ExampleCommand(&m_subsystem).ToPtr());

  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  m_driverController.B().WhileTrue(m_subsystem.ExampleMethodCommand());
}

frc2::Command* RobotContainer::GetAutonomousCommand() 
{
  return m_chooser.GetSelected();
  }
