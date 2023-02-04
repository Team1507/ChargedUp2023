// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Claw.h"

Claw::Claw() 
{
    m_intakeEnabled = false;
}
// This method will be called once per scheduler run
void Claw::Periodic() {}
  
//************************************CLAW******************************************

void Claw::ClawSetPower(float power) 
{
    m_claw.Set(power);
}
float Claw::ClawGetCurrent(void)
{
    return 0;
}
float Claw::ClawGetPower(void)
{
   return m_claw.Get();
}
void Claw::ClawIntakeEnable(bool enable)
{
    m_intakeEnabled = enable;
}

//***********************************Wrist*******************************************

void Claw::WristSetPosition(float position) 
{

}
float Claw::WristGetPosition(void)
{
    return 0;
}

bool Claw::ReadSensorState(void)  //Change Later
{
    return m_ClawGamePiece.Get();
}
void Claw::WristSetPower(float power)     //for Debug use Only 
{
    m_wrist.Set(power);
}
float Claw::WristGetPower(void)           //for Debug use Only 
{
    return m_wrist.Get();
}
