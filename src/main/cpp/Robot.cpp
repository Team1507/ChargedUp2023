// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>
#include <iostream>
#include <frc/DriverStation.h>
// #include <cstdlib>

void Robot::RobotInit() 
{
 //*************************** INIT ******************************
  
  std::cout<<"RobotInit"<<std::endl;
  std::cout<<"FRC2023: ChargedUp"<<std::endl;
  std::cout<<"Version: " << __DATE__ <<"  "<<__TIME__<<std::endl<<std::endl; 

  //Subsystem Initialization
  m_container.m_drivetrain.Stop();
  m_container.m_drivetrain.HardResetDriveEncoders();
  //m_container.m_drivetrain.ResetDriveEncoders();
  m_container.m_drivetrain.ResetSteerEncoders();
  m_container.m_drivetrain.ZeroGyro(); 
  m_container.m_drivetrain.ResetOdometry();
  m_container.m_drivetrain.SetDriveType(Drivetrain::driveType::FIELDCENTRIC); //default to fieldcentric mode
  #ifndef DRIVETRAIN_ONLY
  m_container.m_claw.ClawSetIntakePower(0.4);
  m_container.m_claw.ClawSetOuttakePower(-.8);
  m_container.m_pouch.SetRampPosition(false);
  m_container.m_pouch.InnerIntakeSetPosition(0.0);
  m_container.m_arm.AirSpringSetPosition(true);
  // m_container.m_arm.ElevationArmSetPosition(ArmLevel::Level_Pouch);
  #endif
  CheckAlliance();

}

void Robot::CheckAlliance( void )
{

  //Set Panel LEDs
  #ifndef DRIVETRAIN_ONLY
  if( frc::DriverStation::GetAlliance() == frc::DriverStation::kRed)
  {
      m_container.m_driverfeedback.DriverFeedbackLED(COLOR_RED);
      std::cout << "RED" << std::endl;
  }
  else if(frc::DriverStation::GetAlliance() == frc::DriverStation::kBlue)
  {
      m_container.m_driverfeedback.DriverFeedbackLED(COLOR_BLUE);
      std::cout << "BLUE" << std::endl;
  }
  else
  {
     m_container.m_driverfeedback.DriverFeedbackLED(COLOR_BLUE);
     std::cout << "INVALID BLUE" << std::endl;
  }
  #endif


}


void Robot::RobotPeriodic()
 {
  frc2::CommandScheduler::GetInstance().Run();
  WriteToSmartDashboard();

}


void Robot::DisabledInit() 
{
  std::cout<<"Disabled Init"<<std::endl;
  m_container.m_claw.WristSetPower(-.2);
  // m_container.m_driverfeedback.DriverFeedbackLED(COLOR_CLEAR);
}
 
void Robot::DisabledPeriodic() 
{
  // switch (rand() %3)
  // {
  // case 0:
  //   m_container.m_driverfeedback.DriverFeedbackLED(COLOR_RED);
  //   break;
  // case 1:
  //   m_container.m_driverfeedback.DriverFeedbackLED(COLOR_GREEN);
  //   break;
  // case 2:
  //   m_container.m_driverfeedback.DriverFeedbackLED(COLOR_BLUE);
  // }
}


void Robot::AutonomousInit() 
{
   std::cout<<" **** Auto Init ******"<<std::endl;

   //m_container.m_drivetrain.SetAngleOffset(90.0);
  m_container.m_claw.ClawSetPower(.04);

  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand) {
    m_autonomousCommand->Schedule();
  }
    m_container.m_drivetrain.SetAngleOffset(90); // NOT OFFICIAL!!!!!



}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() 
{
  std::cout<<"Teleop Init"<<std::endl;


  if (m_autonomousCommand) {
    m_autonomousCommand->Cancel();
  }
 }


void Robot::TeleopPeriodic() {}


void Robot::WriteToSmartDashboard(void)
{

  //XBox Controllers
  frc::SmartDashboard::PutNumber("Xbox Left-Y",   (double)m_container.m_botDriver.GetLeftY()    ); 
  frc::SmartDashboard::PutNumber("Xbox Left-X",   (double)m_container.m_botDriver.GetLeftX()    ); 
  frc::SmartDashboard::PutNumber("Xbox Right-X",  (double)m_container.m_botDriver.GetRightX()   ); 
  frc::SmartDashboard::PutBoolean("DriveType",    (bool)m_container.m_drivetrain.GetDriveType() ); 
  //Nax-X
  frc::SmartDashboard::PutBoolean("navx_IsConn",  m_container.m_drivetrain.IsGyroConnected() );
  frc::SmartDashboard::PutNumber("navx_Yaw",      m_container.m_drivetrain.GetGyroYaw()      );
  frc::SmartDashboard::PutNumber("navx_Angle",    m_container.m_drivetrain.GetGyroAngle()    );
  frc::SmartDashboard::PutNumber("navx_Pitch",    m_container.m_drivetrain.GetGyroPitch()    );
  frc::SmartDashboard::PutNumber("navx_Roll",     m_container.m_drivetrain.GetGyroRoll()     );
  //Odometry
  frc::SmartDashboard::PutNumber("odo_X",         m_container.m_drivetrain.GetOdometryX()    );
  frc::SmartDashboard::PutNumber("odo_Y",         m_container.m_drivetrain.GetOdometryY()    );
  frc::SmartDashboard::PutNumber( "Average Drive Falcon Tempature", m_container.m_drivetrain.FalconTempGetAverage());
  //Camera
  frc::SmartDashboard::PutNumber("Target Distance",m_container.m_camera.TargetGetDistance());
  frc::SmartDashboard::PutNumber("Angle to Target",m_container.m_camera.TargetGetYaw());


#ifndef DRIVETRAIN_ONLY
  frc::SmartDashboard::PutBoolean("Turret Right Limit Switch", m_container.m_arm.TurretGetRightLimitSW());
  frc::SmartDashboard::PutBoolean("Turret Left Limit Switch", m_container.m_arm.TurretGetLeftLimitSW());
  frc::SmartDashboard::PutNumber("Turret Encoder", m_container.m_arm.TurretGetEncoder());
  frc::SmartDashboard::PutNumber("Turret Angle", m_container.m_arm.TurretGetAngle());
  frc::SmartDashboard::PutNumber("Arm Position", m_container.m_arm.ElevationArmGetPosition());
#endif
}




void Robot::TestPeriodic() {}
void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
