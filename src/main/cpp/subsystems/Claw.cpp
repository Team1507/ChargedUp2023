// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Claw.h"

Claw::Claw() 
{
    m_intakeEnabled = false;
    
    m_wrist.RestoreFactoryDefaults();
    m_wrist.SetClosedLoopRampRate(0.0); //!!! CHANGE LATER !!!
    m_wristEncoder.SetPosition(0);
    m_wristPID.SetP(0.0); //!!! CHANGE LATER !!!
    m_wristPID.SetI(0.0); //!!! CHANGE LATER !!!
    m_wristPID.SetD(0.0); //!!! CHANGE LATER !!!
    m_wristPID.SetSmartMotionAllowedClosedLoopError(0.0); //!!! CHANGE LATER !!!

    m_claw.RestoreFactoryDefaults();
    m_claw.SetClosedLoopRampRate(0.0); //!!! CHANGE LATER !!!
}
// This method will be called once per scheduler run
void Claw::Periodic() 
{
    frc::SmartDashboard::PutNumber("Wrist Position", m_wristEncoder.GetPosition());
    frc::SmartDashboard::PutBoolean("Forward Limit Switch", m_wristFWDLimit.Get());
    frc::SmartDashboard::PutBoolean("Reverse Limit Switch", m_wristREVLimit.Get());
}
  
//************************************Claw******************************************

void Claw::ClawSetPower(float power) 
{
    m_claw.Set(power);
}
float Claw::ClawGetCurrent(void)
{
    return m_claw.GetOutputCurrent();
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
    m_wristEncoder.SetPosition(position);
}
float Claw::WristGetPosition(void)
{
    return m_wristEncoder.GetPosition();
}

bool Claw::ReadSensorState(void)  //Change Later
{
    return m_clawGamePiece.Get();
}
void Claw::WristSetPower(float power)     //for Debug use Only 
{
    m_wrist.Set(power);
}
float Claw::WristGetPower(void)           //for Debug use Only 
{
    return m_wrist.Get();
}
