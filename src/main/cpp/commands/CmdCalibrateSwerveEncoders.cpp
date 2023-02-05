// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdCalibrateSwerveEncoders.h"
#include <iostream>

CmdCalibrateSwerveEncoders::CmdCalibrateSwerveEncoders( Drivetrain *drivetrain, int step ) 
{
  m_step = step;
  m_drivetrain = drivetrain;
}


void CmdCalibrateSwerveEncoders::Initialize() 
{
  if( m_step == 1 )
  {
    std::cout<<"Calibrate:  Step 1"<<std::endl;
    m_drivetrain->CalibrateSteerEncoderAbsoutePositionStart();
  }
  if( m_step == 2 )
  {
    std::cout<<"Calibrate:  Step 2"<<std::endl;
    m_drivetrain->CalibrateSteerEncoderAbsoutePositionOffset();
  }

}
