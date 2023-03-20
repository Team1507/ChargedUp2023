#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>
#include <frc/AddressableLED.h>
#include "Constants.h"
#include "ctre/Phoenix.h"

//*************COLORS***************

#define COLOR_RED   50, 0, 0
#define COLOR_GREEN 0, 255, 0
#define COLOR_BLUE  0, 0, 50

#define COLOR_YELLOW 255, 255, 0
#define COLOR_PURPLE 128, 0, 128
#define COLOR_ORANGE 255, 160, 0

#define COLOR_CLEAR 0, 0, 0
//**********************************

class DriverFeedback : public frc2::SubsystemBase {
 public:
  DriverFeedback(frc::XboxController *topDriver);

  void Periodic() override;
  void Rumble(float power);
  void DriverFeedbackLED(int r, int g, int b);

  private:
  frc::XboxController *m_topDriver;
  CANifier m_driverLED{CAN_LED_DRIVER};
};
