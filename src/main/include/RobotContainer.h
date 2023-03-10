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
#include <frc/XboxController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/PowerDistribution.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc/DriverStation.h>

#define GAMEPADMAP_BUTTON_START 8
#define GAMEPADMAP_BUTTON_A     1
#define GAMEPADMAP_BUTTON_Y     4

//Autos
#include "commands/AutoDoNothing.h"
#include "commands/AutoTwoPieceLeft.h"
#include "commands/AutoChargeStation.h"
#include "commands/AutoFarConeAndDock.h"
#include "commands/AutoOverAndBack.h"
#include "commands/AutoScoreLink.h"
#include "commands/AutoTwoPieceRight.h"
#include "commands/AutoMoveToCone.h"


//Compile Drivetrain ONLY duringg development so we can use the test swerve base. 
//  #define DRIVETRAIN_ONLY

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


  //****************Controllers*******************
  frc::XboxController m_botDriver{0};
  frc::XboxController m_topDriver{1};
  frc::PowerDistribution m_pdh{CAN_PDH_ID,frc::PowerDistribution::ModuleType::kRev};

#ifndef DRIVETRAIN_ONLY
#endif

  //****************Subsystems*******************
  Drivetrain     m_drivetrain;
  DriverFeedback m_driverfeedback {&m_topDriver};
  Claw           m_claw{&m_pdh};
  Pouch          m_pouch{&m_pdh};
  Arm            m_arm{&m_pouch};
  Toperator      m_toperator;
  Camera         m_camera {&m_driverfeedback};

#ifndef DRIVETRAIN_ONLY
#endif

  frc2::Command* GetAutonomousCommand();


//*********************AUTO**********************
#ifndef DRIVETRAIN_ONLY
 AutoDoNothing     m_autoDoNothing {&m_drivetrain};
 //AutoTwoPieceLeft  m_autoTwoPieceLeft {&m_drivetrain, &m_arm, &m_claw, &m_camera, &m_pouch};
 //AutoTwoPieceRight m_autoTwoPieceRight {&m_drivetrain, &m_arm, &m_claw, &m_camera, &m_pouch};
 AutoChargeStation m_autoChargeStation{&m_drivetrain, &m_arm,  &m_camera, &m_claw, &m_pouch};
 AutoMoveToCone    m_autoMoveToCone{&m_drivetrain, &m_arm, &m_camera, &m_claw, &m_pouch};
 //AutoScoreLink     m_autoScoreLink{&m_drivetrain, &m_arm, &m_claw, &m_camera, &m_pouch};
#endif






 private:
  frc::SendableChooser<frc2::Command*> m_chooser;

  void ConfigureBindings();

  frc2::JoystickButton m_botDriver_START {&m_botDriver, GAMEPADMAP_BUTTON_START};
  frc2::JoystickButton m_botDriver_Y     {&m_botDriver, GAMEPADMAP_BUTTON_Y};
  frc2::JoystickButton m_botDriver_A     {&m_botDriver, GAMEPADMAP_BUTTON_A};






};
