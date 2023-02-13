// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>
#include <iostream>
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


}


void Robot::RobotPeriodic()
 {
  frc2::CommandScheduler::GetInstance().Run();
  WriteToSmartDashboard();

}


void Robot::DisabledInit() 
{
  std::cout<<"Disabled Init"<<std::endl;
 }
 
void Robot::DisabledPeriodic() {}


void Robot::AutonomousInit() 
{
   std::cout<<" **** Auto Init ******"<<std::endl;

   //m_container.m_drivetrain.SetAngleOffset(90.0);

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



#ifndef DRIVETRAIN_ONLY
  frc::SmartDashboard::PutBoolean("Right Limit Switch", m_container.m_arm.TurretGetRightLimitSW());
  frc::SmartDashboard::PutBoolean("Left Limit Switch", m_container.m_arm.TurretGetLeftLimitSW());
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
