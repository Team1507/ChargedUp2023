// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>
#include <frc/AddressableLED.h>
#include "Constants.h"
#include "ctre/Phoenix.h"

class DriverFeedback : public frc2::SubsystemBase {
 public:
  DriverFeedback(frc::XboxController *topDriver);

 /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void Rumble(float power);
  void UnderGlow(int r, int g, int b);
  void DriverFeedbackLED(int r, int g, int b);


  private:
  frc::XboxController *m_topDriver;
  CANifier m_underGlow{CAN_LED_UNDERGLOW};
  

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
