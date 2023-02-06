// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>
#include "subsystems/DriverFeedback.h"
#include "subsystems/Arm.h"
#include "subsystems/Claw.h"
#include "subsystems/Pouch.h"
#include "subsystems/Toperator.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Camera.h"
#include "Constants.h"
#include "subsystems/ExampleSubsystem.h"
#include <frc/XboxController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/PowerDistribution.h>

//Autos
#include "commands/AutoDoNothing.h"


//Compile Drivetrain ONLY duringg development so we can use the test swerve base. 
#define DRIVETRAIN_ONLY

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and trigger mappings) should be declared here.
 */
class RobotContainer 
{
 public:
  RobotContainer();

  ExampleSubsystem m_subsystem;

  //****************Controllers*******************
  frc::XboxController m_botDriver{0};

#ifndef DRIVETRAIN_ONLY
  frc::XboxController m_topDriver{1};
  frc::PowerDistribution m_pdh{CAN_PDH_ID,frc::PowerDistribution::ModuleType::kRev};
#endif

  //****************Subsystems*******************
  Drivetrain     m_drivetrain;

#ifndef DRIVETRAIN_ONLY
  DriverFeedback m_driverfeedback {&m_topDriver};
  Arm            m_arm;
  Claw           m_claw{&m_pdh};
  Pouch          m_pouch;
  Toperator      m_toperator;
  Camera         m_camera;
#endif

  frc2::Command* GetAutonomousCommand();


//*********************AUTO**********************
 AutoDoNothing m_autoDoNothing {&m_drivetrain};









 private:
  // Replace with CommandPS4Controller or CommandJoystick if needed
  frc2::CommandXboxController m_driverController{
  OperatorConstants::kDriverControllerPort};
  frc::SendableChooser<frc2::Command*> m_chooser;

  void ConfigureBindings();
};
