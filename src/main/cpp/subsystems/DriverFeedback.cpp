// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/DriverFeedback.h"

// DriverFeedback(frc::XboxController *operator)
DriverFeedback::DriverFeedback(frc::XboxController *topDriver) 
{
    m_topDriver = topDriver;
  //  m_underGlow.ConfigFactoryDefault();
   m_driverLED.ConfigFactoryDefault();

}

// This method will be called once per scheduler run
void DriverFeedback::Periodic() {}
void DriverFeedback::Rumble(float power) 
{
    m_topDriver->SetRumble(frc::GenericHID::RumbleType::kBothRumble,power);
}
void DriverFeedback::UnderGlow(int r, int g, int b)
{
    // m_underGlow.SetLEDOutput(r,CANifier::LEDChannelA);
    // m_underGlow.SetLEDOutput(g,CANifier::LEDChannelB);
    // m_underGlow.SetLEDOutput(b,CANifier::LEDChannelC);
}
void DriverFeedback::DriverFeedbackLED(int r, int g, int b)
{
    m_driverLED.SetLEDOutput(r,CANifier::LEDChannelB);
    m_driverLED.SetLEDOutput(g,CANifier::LEDChannelC);
    m_driverLED.SetLEDOutput(b,CANifier::LEDChannelA);
}