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
#include "Constants.h"
#include "subsystems/ExampleSubsystem.h"
#include <frc/XboxController.h>
#include "commands/AutoDoNothing.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/PowerDistribution.h>

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
    // The robot's subsystems are defined here...

  frc::PowerDistribution m_pdh{CAN_PDH_ID,frc::PowerDistribution::ModuleType::kRev};
  frc::XboxController m_botDriver{0};
  frc::XboxController m_topDriver{1};
  DriverFeedback m_driverfeedback {&m_topDriver};
  Arm m_arm;
  Claw m_claw{&m_pdh};
  Pouch m_pouch;
  Toperator m_toperator;
  frc2::Command* GetAutonomousCommand();




//*********************AUTO**********************
 AutoDoNothing m_autoDoNothing {/*&m_drivetrain*/};









 private:
  // Replace with CommandPS4Controller or CommandJoystick if needed
  frc2::CommandXboxController m_driverController{
  OperatorConstants::kDriverControllerPort};
  frc::SendableChooser<frc2::Command*> m_chooser;

  void ConfigureBindings();
};
