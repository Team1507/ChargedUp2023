// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdTurretTurn2Angle.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
CmdTurretTurn2Angle::CmdTurretTurn2Angle(Arm *arm, double angle) 
{
  m_angle = angle;
  m_arm = arm;
}

// Called when the command is initially scheduled.
void CmdTurretTurn2Angle::Initialize() 
{
m_arm->TurretTurn2Angle(m_angle);
}
