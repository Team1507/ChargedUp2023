#include "subsystems/DriverFeedback.h"

DriverFeedback::DriverFeedback(frc::XboxController *botDriver,frc::XboxController *topDriver) 
{
   m_botDriver = botDriver;    
   m_topDriver = topDriver;

   m_driverLED.ConfigFactoryDefault();

}

void DriverFeedback::Periodic() {}

void DriverFeedback::RumbleBot(float power) 
{
    m_botDriver->SetRumble(frc::GenericHID::RumbleType::kBothRumble,power);
}
void DriverFeedback::RumbleTop(float power) 
{
    m_topDriver->SetRumble(frc::GenericHID::RumbleType::kBothRumble,power);
}

void DriverFeedback::DriverFeedbackLED(int r, int g, int b)
{
    m_driverLED.SetLEDOutput(r,CANifier::LEDChannelB);
    m_driverLED.SetLEDOutput(g,CANifier::LEDChannelC);
    m_driverLED.SetLEDOutput(b,CANifier::LEDChannelA);
}