// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SwerveModule.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Robot.h"
#include <iostream>


//Falcon steer ticks per degree
// MK4i steer ratio 150/7:1.   Integrated encoder = 2048 ticks/rotation
// Therefore 150/7 * 2048 =43885.7
#define STEER_ENCODER_TICKS_PER_DEGREE    (43885.7/360.0)

//Falcon drive ticks per inch
//MK4i drive ratio = 6.75:1
//Integrated encoder = 2048 ticks/rotation
//Tire diameter = 4inches,  circumference =4PI   (C=2*PI*r) 
//Therefore (2048 * 6.75)/4PI = 1100
#define DRIVE_ENCODER_TICKS_PER_INCH      (1100)            //Needs to be verified


//Drive Velocity PID
const double DRIVE_PID_kF = 0.0475;
const double DRIVE_PID_kP = 0.05;
const double DRIVE_PID_kI = 0.0;
const double DRIVE_PID_kD = 0.0;

//Steer PID
const double STEER_PID_kF = 0.0;
const double STEER_PID_kP = 0.125;      //0.075;
const double STEER_PID_kI = 0.0;
const double STEER_PID_kD = 0.0;


SwerveModule::SwerveModule(int driveMotorCanID, int steerMotorCanID, int steerEncoderCanID, std::string debugID )
            : m_driveMotor(driveMotorCanID,"SwerveDrive"),
              m_steerMotor(steerMotorCanID,"SwerveDrive"),
              m_steerEncoder(steerEncoderCanID,"SwerveDrive"),
              m_dbgID(debugID)
{

    //Initialize Drive Motor
    m_driveMotor.ConfigFactoryDefault();
    m_driveMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,10);
    m_driveMotor.SetInverted( false );
    m_driveMotor.SetNeutralMode(NeutralMode::Brake);
    m_driveMotor.SetSelectedSensorPosition(0.0,0,10);

    m_driveMotor.ConfigVoltageCompSaturation(12.0,10);
    m_driveMotor.EnableVoltageCompensation(true);

    m_driveMotor.ConfigOpenloopRamp(0.5,0);
    m_driveMotor.ConfigClosedloopRamp(0.5,0);

    m_driveMotor.ConfigNeutralDeadband(0.001,10);   //Minimal deadband in drive falcon to prevent stuttering at slow speed

    //Initialize drive PID
    m_driveMotor.Config_kF(0, DRIVE_PID_kF, 10);
    m_driveMotor.Config_kP(0, DRIVE_PID_kP, 10);
    m_driveMotor.Config_kI(0, DRIVE_PID_kI, 10);
    m_driveMotor.Config_kD(0, DRIVE_PID_kD, 10);

    //Initialize steer Motor
    m_steerMotor.ConfigFactoryDefault();
    m_steerMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,10);
    m_steerMotor.SetInverted( true );
    m_steerMotor.SetNeutralMode(NeutralMode::Brake);
    m_steerMotor.SetSelectedSensorPosition(0.0,0,10);

    m_steerMotor.ConfigVoltageCompSaturation(12.0,10);
    m_steerMotor.EnableVoltageCompensation(true);

    //Initialize steer PID
    m_steerMotor.Config_kF(0, STEER_PID_kF, 10);
    m_steerMotor.Config_kP(0, STEER_PID_kP, 10);
    m_steerMotor.Config_kI(0, STEER_PID_kI, 10);
    m_steerMotor.Config_kD(0, STEER_PID_kD, 10);

    m_steerMotor.ConfigAllowableClosedloopError( 0, 0.25 * STEER_ENCODER_TICKS_PER_DEGREE, 10 );



    //Initialise Steer Encoder
    m_steerEncoder.ConfigAbsoluteSensorRange(AbsoluteSensorRange::Signed_PlusMinus180 );    //Sets angle range as -180 to + 180
    m_steerEncoder.ConfigSensorDirection(false);                                            //+angle CounterClockwise turn



    //Init members
    m_desired_steer_angle = 90.0;   //Steer Angle of 90 = forward
    m_drive_encoder_zero  = 0;

    ResetModuleOdometry();

    std::cout << "Module Debug ID= " << m_dbgID << std::endl;

}

// This method will be called once per scheduler run
void SwerveModule::Periodic() 
{

    //Debug Output
    // frc::SmartDashboard::PutNumber(m_dbgID + "-EncAbs",  GetSteerEncoderAbsoutePosition() ); 
    // frc::SmartDashboard::PutNumber(m_dbgID + "-EncPos",  GetSteerEncoderPosition() ); 
    // frc::SmartDashboard::PutNumber(m_dbgID + "-MotPos",  GetSteerMotorPosition() ); 
    // frc::SmartDashboard::PutNumber(m_dbgID + "-AngReq",  m_desired_steer_angle ); 

    // frc::SmartDashboard::PutNumber(m_dbgID + "-DrvEnc",  GetDriveEncoder() ); 
    // frc::SmartDashboard::PutBoolean(m_dbgID+ "-DrvInv",  m_invert_drive ); 

    frc::SmartDashboard::PutNumber(m_dbgID + "-DrvPwr",  m_driveMotor.GetMotorOutputPercent() ); 
    frc::SmartDashboard::PutNumber(m_dbgID + "-DrvVel",  m_driveMotor.GetSelectedSensorVelocity(0) ); 
    frc::SmartDashboard::PutNumber(m_dbgID + "-DrvTemp",  m_driveMotor.GetTemperature() ); 

}



//Set angle of module
//Input Range[-180 to 180]
//Deturmines the shortest turning path (CW or CCW) to desired angle
//Note: This function does not utilize the optimized invert drive feature!!!
void SwerveModule::SetSteerAngle( float angle )
{
    m_desired_steer_angle = angle;

    //Get current position of the drive motor
    float curr_steer_angle    = GetSteerEncoderAbsoutePosition();               //return in degrees [-180:180]

    float angle_error = m_desired_steer_angle - curr_steer_angle;               //Calculate angle delta, +error = CCW move

    //if angle error is > 180, its faster to go the oppisite way
    if( angle_error >=  180.0 )  angle_error -= 360.0;
    if( angle_error <= -180.0 )  angle_error += 360.0;


    float curr_steer_position = m_steerMotor.GetSelectedSensorPosition(0);      //return in encoder counts

    float target_position = curr_steer_position + (angle_error* STEER_ENCODER_TICKS_PER_DEGREE);  

    //Update steer motor positional PID controller
    m_steerMotor.Set(ControlMode::Position,  target_position );
    m_invert_drive = false;    
}


//Set angle of module
//Input Range[-180 to 180]
//Uses Drive motor inversion to limit maximum steer angle move to +/- 90 degrees.
void SwerveModule::SetSteerAngleV2( float angle )
{

    bool invert_drive     = false;      //Assume no inversion needed
    m_desired_steer_angle = angle;      //Store for reference

    //Get current position of the drive motor
    float curr_steer_angle    = GetSteerEncoderAbsoutePosition();               //return in degrees [-180:180]

    float angle_error = m_desired_steer_angle - curr_steer_angle;               //Calculate angle delta, +error = CCW move


    //Bound error to +/- 180
    if( angle_error >  180.0 ) { angle_error -= 360.0; }
    if( angle_error < -180.0 ) { angle_error += 360.0; }

    //Check angle to minimize steering turn angle
    if( angle_error >=   90.0 ) { angle_error -= 180.0;     invert_drive = true;    }
    if( angle_error <=  -90.0 ) { angle_error += 180.0;     invert_drive = true;    }


    //Now with angle error, caculate how many motor encoder ticks it needs to move
    float curr_steer_position = m_steerMotor.GetSelectedSensorPosition(0);      //return in encoder counts

    float target_position = curr_steer_position + (angle_error* STEER_ENCODER_TICKS_PER_DEGREE);  


    //Update steer motor positional PID controller
    m_steerMotor.Set(ControlMode::Position,  target_position );
    m_invert_drive = invert_drive;

}



//  *** Steering Encoder **

// Get relative encoder position since reset.  Does not wrap, keep incrementing 
double SwerveModule::GetSteerEncoderPosition(void)
{
    return m_steerEncoder.GetPosition();
}

// Get Absolute position, range [-180, 180]
double SwerveModule::GetSteerEncoderAbsoutePosition(void)
{
    return m_steerEncoder.GetAbsolutePosition();    
}

// Get relative position from motor
double SwerveModule::GetSteerMotorPosition(void)
{
    return m_steerMotor.GetSelectedSensorPosition(0) / STEER_ENCODER_TICKS_PER_DEGREE;    
}

void SwerveModule::ResetSteerEncoders(void)
{
    //Align encoders to Absolute Encoder
    m_steerEncoder.SetPosition( GetSteerEncoderAbsoutePosition() );             //Cancoder relative position encoder                          
    m_steerMotor.SetSelectedSensorPosition( GetSteerEncoderAbsoutePosition() * STEER_ENCODER_TICKS_PER_DEGREE );  //Motor encoder
}



//  *** Drive Encoder **
int  SwerveModule::GetDriveEncoder(void)
{
    return (m_driveMotor.GetSelectedSensorPosition(0) - m_drive_encoder_zero);
}
void SwerveModule::HardResetDriveEncoder(void)
{
    //Takes several cycles to complete
    m_driveMotor.SetSelectedSensorPosition(0);
    m_drive_encoder_zero = 0;
}
void SwerveModule::SoftResetDriveEncoder(void)
{
    m_drive_encoder_zero = m_driveMotor.GetSelectedSensorPosition(0);
}




float SwerveModule::GetDriveMotor( void )
{
    return m_driveMotor.GetMotorOutputPercent();
}
float SwerveModule::GetSteerMotor( void )
{
    return m_steerMotor.GetMotorOutputPercent();
}
void SwerveModule::SetDriveMotor( float power )
{
    frc::SmartDashboard::PutNumber(m_dbgID + "-ReqDVeloc",  0 ); 
    if( m_invert_drive )
        m_driveMotor.Set(ControlMode::PercentOutput, -power);
    else
        m_driveMotor.Set(ControlMode::PercentOutput,  power);
}
void SwerveModule::SetDriveVelocity( float speed )
{
    frc::SmartDashboard::PutNumber(m_dbgID + "-ReqDVeloc",  speed ); 
    if( m_invert_drive )
        m_driveMotor.Set(ControlMode::Velocity, -speed);
    else
        m_driveMotor.Set(ControlMode::Velocity,  speed);
}

float SwerveModule::GetFalconTemp(void)
{
    return m_driveMotor.GetTemperature();
}


bool SwerveModule::GetDriveInvertion( void )
{
    return m_invert_drive;
}




//**************** Odometry *********************
void SwerveModule::ModuleOdometryPeriodic(void)
{
    //Read Encoders and find delta distance traveled in inches
    int curr_drive_encoder  = GetDriveEncoder();

    float delta_encoder  = (float)(curr_drive_encoder  - m_prev_drive_encoder)  / DRIVE_ENCODER_TICKS_PER_INCH;

    //Calculate new X and Y of module based steer heading
    float angle = GetModuleOdometryHeading() * M_PI/180.0; //converted to radians

    m_delta_x = delta_encoder * cosf( angle );
    m_delta_y = delta_encoder * sinf( angle );
     
    //Add delta to running total
    m_curr_x += m_delta_x;
    m_curr_y += m_delta_y;

    //Calculate Velocity
    float curr_timestamp = (double)m_timer.GetFPGATimestamp();  //Get current time
    float delta_time = curr_timestamp - m_prev_timestamp;       //delta from last time

    m_curr_v  =  delta_encoder / delta_time;                    //v=delta d / delta v


    //Update parameters for next run
    m_prev_drive_encoder  = curr_drive_encoder;
    m_prev_timestamp      = curr_timestamp;
}

//********************************************
void SwerveModule::ResetModuleOdometry(void)
{
    SoftResetDriveEncoder();
    m_prev_drive_encoder  = 0;
    m_prev_timestamp = (double)m_timer.GetFPGATimestamp();

    m_curr_x  = 0.0;
    m_curr_y  = 0.0;
    m_curr_v  = 0.0;

    m_delta_x = 0.0;
    m_delta_y = 0.0;

}

float  SwerveModule::GetModuleOdometryX(void)
{
    return m_curr_x;
}

float  SwerveModule::GetModuleOdometryY(void)
{
    return m_curr_y;
}


float  SwerveModule::GetModuleOdometryDeltaX(void)
{
    return m_delta_x;
}

float  SwerveModule::GetModuleOdometryDeltaY(void)
{
    return m_delta_y;
}

float  SwerveModule::GetModuleOdometryVel(void)
{
    return m_curr_v;
}

float  SwerveModule::GetModuleOdometryHeading(void)
{
    return m_steerEncoder.GetAbsolutePosition();
}







/*
 * Testing Methods Only!
 */
void SwerveModule::SetSteerMotor( float power )
{
    m_steerMotor.Set(ControlMode::PercentOutput, power);
}


//*********************************************
// *** CANCoder Absolute Position Calibration
//     **Note 1: Should only be done ONCE when calibrating swerve module
//     **Note 2: Wheels must be aligned to 0 degree position before running this procedure
//  Due to delay in the can bus, this must be done in 2 steps:
//    1) Zero Magnet offet - clears out any previous calibration
//   -delay-
//    2) Get position error then set magnet offset to zero absolute encoder  
void SwerveModule::CalibrateSteerEncoderAbsoutePositionStart(void)
{
    m_steerEncoder.ConfigFactoryDefault();
    m_steerEncoder.ConfigMagnetOffset( 0.0 );                           //Clear offset
}
void SwerveModule::CalibrateSteerEncoderAbsoutePositionOffset(void)
{
    double curr_abs_position = m_steerEncoder.GetAbsolutePosition();    //Get Position, which is our new offset error
    m_steerEncoder.ConfigMagnetOffset( -curr_abs_position, 10);         //Set Magnetic offset with offset error
}


