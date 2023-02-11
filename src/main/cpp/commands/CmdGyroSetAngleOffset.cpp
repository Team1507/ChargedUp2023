// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdGyroSetAngleOffset.h"


CmdGyroSetAngleOffset::CmdGyroSetAngleOffset(Drivetrain *drivetrain, float angle) 
{
  m_drivetrain = drivetrain;
  m_angle      = angle;
}


void CmdGyroSetAngleOffset::Initialize() 
{
  m_drivetrain->SetAngleOffset(m_angle);
}
