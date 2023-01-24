// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Pouch.h"

Pouch::Pouch() = default;

void Pouch::SetIntakePower(float power,Intake type)
{
    if(Intake::Inner == type)
    {
        
    } 
    else if (Intake::Outer == type)
    {
    
    }
}
float Pouch::ReadSensorState(void)
{

}
void Pouch::SetRampPosition(float position)
{

}
void Pouch::DeployIntake(Intake type)
{
   if(Intake::Inner == type)
    {
        
    } 
    else if (Intake::Outer == type)
    {
    
    }
}
void Pouch::RetractIntake(Intake type)
{
    if(Intake::Inner == type)
    {
        
    } 
    else if (Intake::Outer == type)
    {
    
    }
}

// This method will be called once per scheduler run
void Pouch::Periodic() {}
