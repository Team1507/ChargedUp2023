// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveTypeToggle.h"

CmdDriveTypeToggle::CmdDriveTypeToggle( Drivetrain *drivetrain ) 
{
  m_drivetrain = drivetrain;
}

void CmdDriveTypeToggle::Initialize() 
{
  switch( m_drivetrain->GetDriveType() )
  {
    case Drivetrain::ROBOTCENTRIC:
      m_drivetrain->SetDriveType( Drivetrain::FIELDCENTRIC );
      break;
    case Drivetrain::FIELDCENTRIC:
      m_drivetrain->SetDriveType( Drivetrain::ROBOTCENTRIC );
      break;
    
  }
}
