// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Arm.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

#define TicksPerAngle (-159.0/90.0)

#define Ticks2Angle(ticks) (ticks / TicksPerAngle) 
#define Angle2Ticks(angle) (angle * TicksPerAngle)

Arm::Arm(Pouch *pouch) 
{
    m_pouch = pouch;
    m_limitPressed = false;
    m_turret.RestoreFactoryDefaults(); 
    m_turretEncoder.SetPosition(0.0); 
    m_turretPID.SetP(0.02); // change later
    m_turretPID.SetI(0.0); // change later
    m_turretPID.SetD(0.0); // change later
    m_turretPID.SetSmartMotionAllowedClosedLoopError(0.5); // change later
    m_turret.SetOpenLoopRampRate(1.0); // change later
    m_turretPID.SetOutputRange(-0.7,0.7,0);
    //Turret 0 to not assume that it start at 0
    m_turretPID.SetReference(0, rev::CANSparkMax::ControlType::kPosition);

}

void Arm::Periodic() 
{
    frc::SmartDashboard::PutBoolean("Elevation Home Limit Switch", ElevationHomeLimitSwitch());
    frc::SmartDashboard::PutNumber("Turret Wanted Position",m_wanted_position);
    if(TurretGetLeftLimitSW() && !m_limitPressed)
    {
        TurretSetEncoder(0.0);
        m_limitPressed = true;
    }
    else if(TurretGetLeftLimitSW() && m_limitPressed)
    {
        m_limitPressed = false;
    }
    
}

//**********************************Turret******************************

void Arm::TurretTurn2Angle(float angle) 
{
    return;
    //This makes sure we cant move when arm is all of the way down 
    // if(m_elevationHomeLimitSwitch.Get() == true)
    // {
    //     // m_turret.Set(0);
    //     std::cout <<"elevation home limit swtich is pressed"<< std::endl;
    // }
    // else
    // {
    //     // m_turretPID.SetReference(0, rev::CANSparkMax::ControlType::kPosition);
    //     m_wanted_position = angle;
    // }

   
}
void Arm::TurretSetPower(float power) 
{
    //This makes sure we cant move when arm is all of the way down   
    if(m_elevationHomeLimitSwitch.Get() == true)
    {
        m_turret.Set(0.0);
        std::cout <<"elevation home limit swtich is pressed"<< std::endl;
    }
    else
    {
        m_turret.Set(power);
    }

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
bool Arm::TurretGetLeftLimitSW(void)
{
    return m_turretFWDLimit.Get();
}
bool Arm::TurretGetRightLimitSW(void)
{
    return m_turretREVLimit.Get();
}

//***********************************ARM*********************************

void Arm::ElevationArmSetPosition(ArmLevel position) 
{
    switch(position)
    {
        case ArmLevel::Level_Pouch :
            if(m_pouch->IntakeIsDeployed())
            {
                m_lowerArm.Set(frc::DoubleSolenoid::kForward);
                m_upperArm.Set(frc::DoubleSolenoid::kForward);
            }
            break;
        case ArmLevel::Low : 
            if(m_pouch->IntakeIsDeployed() || ElevationArmGetPosition() != Level_Pouch)
            {
                m_upperArm.Set(frc::DoubleSolenoid::kReverse);
                m_lowerArm.Set(frc::DoubleSolenoid::kForward);
            }
            break;
        case ArmLevel::Mid :
            if(m_pouch->IntakeIsDeployed() || ElevationArmGetPosition() != Level_Pouch)
            {
                m_lowerArm.Set(frc::DoubleSolenoid::kReverse);
                m_upperArm.Set(frc::DoubleSolenoid::kForward);
            }
            break;
        case ArmLevel::High :
            if(m_pouch->IntakeIsDeployed() || ElevationArmGetPosition() != Level_Pouch)
            {
                m_lowerArm.Set(frc::DoubleSolenoid::kReverse);
                m_upperArm.Set(frc::DoubleSolenoid::kReverse);                
            }
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


void Arm::AirSpringSetPosition(bool position)
{

    m_airSpring.Set(frc::DoubleSolenoid::kForward);

    // if(position == false)
    // {
    //     m_airSpring.Set(frc::DoubleSolenoid::kReverse);
    // }
}
 

bool Arm::ElevationHomeLimitSwitch(void)
{
    return m_elevationHomeLimitSwitch.Get();
}

ArmLevel Arm::ElevationArmGetPosition(void)
{
    if (m_lowerArm.Get() == frc::DoubleSolenoid::kForward && m_upperArm.Get() == frc::DoubleSolenoid::kForward)
    {
       return ArmLevel::Level_Pouch;
    }
    else if (m_lowerArm.Get() == frc::DoubleSolenoid::kReverse && m_upperArm.Get() == frc::DoubleSolenoid::kReverse)
    {
        return ArmLevel::High;
    }
    else if (m_lowerArm.Get() == frc::DoubleSolenoid::kReverse && m_upperArm.Get() == frc::DoubleSolenoid::kForward)
    {
        return ArmLevel::Mid;
    }
    else if (m_lowerArm.Get() == frc::DoubleSolenoid::kForward && m_upperArm.Get() == frc::DoubleSolenoid::kReverse)
    {
        return ArmLevel::Low;
    }
    else
    {
        return ArmLevel::Level_Pouch;
    }
    
}
