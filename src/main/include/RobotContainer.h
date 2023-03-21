// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#define GAMEPADMAP_BUTTON_START 8
#define GAMEPADMAP_BUTTON_A     1
#define GAMEPADMAP_BUTTON_Y     4

// #define DRIVETRAIN_ONLY
// #define TURRET

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>
#include "Constants.h"
#include <frc/XboxController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/PowerDistribution.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc/DriverStation.h>
#include "subsystems/Drivetrain.h"

#ifndef DRIVETRAIN_ONLY

#include "subsystems/DriverFeedback.h"
#include "subsystems/Arm.h"
#include "subsystems/Claw.h"
#include "subsystems/Pouch.h"
#include "subsystems/Toperator.h"
#include "subsystems/Camera.h"

//Autos
#include "commands/AutoDoNothing.h"
#include "commands/AutoChargeStation.h"
#include "commands/AutoTwoPieceBlue.h"
#include "commands/AutoPowerStripBlue.h"
#include "commands/AutoTwoPieceRed.h"
#include "commands/AutoPowerStripRed.h"

#endif



class RobotContainer 
{
 public:
  RobotContainer();


  //****************Controllers*******************
  frc::XboxController m_botDriver{0};
  frc::XboxController m_topDriver{1};
  frc::PowerDistribution m_pdh{CAN_PDH_ID,frc::PowerDistribution::ModuleType::kRev};

  //****************Subsystems*******************
  Drivetrain     m_drivetrain;

  #ifndef DRIVETRAIN_ONLY
  DriverFeedback m_driverfeedback {&m_botDriver,&m_topDriver};
  Claw           m_claw{&m_pdh};
  Pouch          m_pouch{&m_pdh};
  Arm            m_arm{&m_pouch};
  Toperator      m_toperator;
  Camera         m_camera {&m_driverfeedback};
  #endif

  frc2::Command* GetAutonomousCommand();


//*********************AUTO**********************
#ifndef DRIVETRAIN_ONLY
 AutoDoNothing       m_autoDoNothing     {&m_drivetrain};
 AutoChargeStation   m_autoChargeStation {&m_drivetrain, &m_arm, &m_camera, &m_claw, &m_pouch};
 AutoTwoPieceBlue    m_autoTwoPieceBlue  {&m_drivetrain, &m_arm, &m_camera, &m_claw, &m_pouch};
 AutoPowerStripBlue  m_autoPowerStripBlue{&m_drivetrain, &m_arm, &m_camera, &m_claw ,&m_pouch};
 AutoTwoPieceRed     m_autoTwoPieceRed   {&m_drivetrain, &m_arm, &m_camera, &m_claw, &m_pouch};
 AutoPowerStripRed   m_autoPowerStripRed {&m_drivetrain, &m_arm, &m_camera, &m_claw, &m_pouch};
#endif






 private:
  frc::SendableChooser<frc2::Command*> m_chooser;

  void ConfigureBindings();

  frc2::JoystickButton m_botDriver_START {&m_botDriver, GAMEPADMAP_BUTTON_START};
  frc2::JoystickButton m_botDriver_Y     {&m_botDriver, GAMEPADMAP_BUTTON_Y};
  frc2::JoystickButton m_botDriver_A     {&m_botDriver, GAMEPADMAP_BUTTON_A};






};
