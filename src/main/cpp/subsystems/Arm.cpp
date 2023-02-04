// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Arm.h"
// #define Velocity2RPM(velocity) ((600 * velocity) / (2048))
#define Ticks2Angle(ticks) (ticks) 
#define Angle2Ticks(angle) (angle)
Arm::Arm() 
{
    m_turret.RestoreFactoryDefaults(); 
    m_turretEncoder.SetPosition(0.0); 
    m_turretPID.SetP(0.0); // change later
    m_turretPID.SetI(0.0); // change later
    m_turretPID.SetD(0.0); // change later
    m_turretPID.SetSmartMotionAllowedClosedLoopError(0.0); // change later
    m_turret.SetOpenLoopRampRate(0.0); // change later
}

void Arm::Periodic() {}

//**********************************Turret******************************

void Arm::TurretTurn2Angle(float angle) 
{
    m_turretPID.SetReference(angle, rev::CANSparkMax::ControlType::kPosition);
}
void Arm::TurretSetPower(float power) 
{
    m_turret.Set(power);
}
void Arm::TurretSetEncoder(float encoder) 
{
    m_turretEncoder.SetPosition(encoder);
}
float Arm::TurretGetPower(void) 
{
    return m_turret.Get();
} 
float Arm::TurretGetAngle(void) 
{
    return Ticks2Angle(m_turretEncoder.GetPosition());
} 
float Arm::TurretGetEncoder(void) 
{
    return m_turretEncoder.GetPosition();
}
 
//***********************************ARM*********************************

void Arm::ElevationArmSetPosition(ArmLevel position) 
{
    switch(position)
    {
        case ArmLevel::Level_Pouch :
            m_lowerArm.Set(frc::DoubleSolenoid::kForward);
            m_upperArm.Set(frc::DoubleSolenoid::kForward);
            break;
        case ArmLevel::Low : 
            m_upperArm.Set(frc::DoubleSolenoid::kReverse);
            m_lowerArm.Set(frc::DoubleSolenoid::kForward);
            break;
        case ArmLevel::Mid :
            m_lowerArm.Set(frc::DoubleSolenoid::kReverse);
            m_upperArm.Set(frc::DoubleSolenoid::kForward);
            break;

         case ArmLevel::High :
            m_lowerArm.Set(frc::DoubleSolenoid::kReverse);
            m_upperArm.Set(frc::DoubleSolenoid::kReverse);
            break;
    }
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

