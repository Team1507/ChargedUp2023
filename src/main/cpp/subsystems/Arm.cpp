// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Arm.h"

Arm::Arm() = default;

// This method will be called once per scheduler run
void Arm::Periodic() {}

//**********************************Turret******************************

void Arm::TurretSetAngle(float angle) 
{
    //m_turret.Set(ControlMode::Position, angle);
}
void Arm::TurretSetPower(float power) 
{
    //m_turret.Set(ControlMode::PercentOutput, power);
}
void Arm::TurretSetEncoder(float encoder) 
{
    //m_turret.Set(ControlMode::Position, encoder);
}
float Arm::TurretGetPower(void) 
{
    //m_turret.GetMotorOutputPercent();
} 
float Arm::TurretGetAngle(void) 
{
   // m_turret.GetSelectedSensorPosition();
} 
float Arm::TurretGetEncoder(void) 
{
   // m_turret.GetSelectedSensorPosition();
}
 
//***********************************ARM*********************************

void Arm::ElevationArmSetPosition(int position) 
{

} 
void Arm::ExtensionSetPosition(bool position) 
{
if(position == true)
{
    m_armExtension.Set(frc::DoubleSolenoid::kForward);
}
if(position == false)
{
    m_armExtension.Set(frc::DoubleSolenoid::kReverse);
}
} 


