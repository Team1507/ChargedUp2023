#include "subsystems/DriverFeedback.h"

DriverFeedback::DriverFeedback(frc::XboxController *topDriver) 
{
    m_topDriver = topDriver;
   m_driverLED.ConfigFactoryDefault();

}

void DriverFeedback::Periodic() {}

void DriverFeedback::Rumble(float power) 
{
    m_topDriver->SetRumble(frc::GenericHID::RumbleType::kBothRumble,power);
}

void DriverFeedback::DriverFeedbackLED(int r, int g, int b)
{
    m_driverLED.SetLEDOutput(r,CANifier::LEDChannelB);
    m_driverLED.SetLEDOutput(g,CANifier::LEDChannelC);
    m_driverLED.SetLEDOutput(b,CANifier::LEDChannelA);
}