// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdWristSetPosition.h"

CmdWristSetPosition::CmdWristSetPosition(Claw *claw, float position) 
{
  m_claw = claw;
  m_position = position;
}

// Called when the command is initially scheduled.
void CmdWristSetPosition::Initialize() 
{
  m_claw->WristSetPosition(m_position);
}
