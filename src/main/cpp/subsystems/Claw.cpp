#include "subsystems/Claw.h"

#define WRIST_RESET_POSITION 2.0

Claw::Claw(frc::PowerDistribution *pdh) 
{
    m_intakeEnabled = false;
    m_clawManualOverride = false;
    
    m_wrist.RestoreFactoryDefaults();
    m_wrist.SetClosedLoopRampRate(0.0);
    m_wristEncoder.SetPosition(0);
    m_wristPID.SetP(0.02);
    m_wristPID.SetI(0.0);
    m_wristPID.SetD(0.0);
    m_wristPID.SetSmartMotionAllowedClosedLoopError(0.0);
    m_wristPID.SetOutputRange(-0.3,0.3,0);

    m_wrist.SetInverted(true);

    m_pdh = pdh;

    m_claw.RestoreFactoryDefaults();
    m_claw.SetClosedLoopRampRate(0.0);
    m_claw.SetInverted(false);


}

void Claw::Periodic() 
{
    frc::SmartDashboard::PutNumber("Wrist Position", m_wristEncoder.GetPosition());
    frc::SmartDashboard::PutBoolean("Wrist Up Limit Switch", WristLimitTop());
    frc::SmartDashboard::PutBoolean("Claw Game Piece Photoeye",m_clawGamePiece.Get());
    if(WristLimitTop())
    {
        WristSetPosition(0.0);
        WristHoldPosition(WRIST_RESET_POSITION);
        WristSetHomed(true);
    }
}
  
//************************************CLAW******************************************

void Claw::ClawSetPower(float power) 
{
    m_claw.Set(power);
}
float Claw::ClawGetCurrent(void)
{
    return m_pdh->GetCurrent(PDH_CLAW_PORT);
}
float Claw::ClawGetPower(void)
{
   return m_claw.Get();
}
void Claw::ClawIntakeEnable(bool enable)
{
    m_intakeEnabled = enable;
}
bool Claw::ClawIntakeGetEnable(void)
{
    return m_intakeEnabled; 
}
void Claw::ClawSetIntakePower(float power)
{
    m_clawIntakePower = power;
}
float Claw::ClawGetIntakePower(void)
{
    return m_clawIntakePower;
}
void Claw::ClawSetOuttakePower(float power)
{
    m_clawOuttakePower = power;
}
float Claw::ClawGetOuttakePower(void)
{
    return m_clawOuttakePower;
}

void Claw::ClawSetManualOverride(bool override)
{
    m_clawManualOverride = override;
}
bool Claw::ClawGetManualOverride(void)
{
    return m_clawManualOverride;
}
//***********************************WRIST*******************************************

void Claw::WristSetPosition(float position) 
{
    m_wristEncoder.SetPosition(position);
}
void Claw::WristHoldPosition(float position)
{
    m_wristPID.SetReference(position,rev::CANSparkMax::ControlType::kPosition);
}
float Claw::WristGetPosition(void)
{
    return m_wristEncoder.GetPosition();
}
float Claw::WristGetCurrent(void)
{
    return m_pdh->GetCurrent(PDH_WRIST_PORT);
}

bool Claw::ReadSensorState(void) 
{
    return m_clawGamePiece.Get();
}
void Claw::WristSetPower(float power)     //for Debug use Only 
{
    m_wrist.Set(power);
}
float Claw::WristGetPower(void)           //for Debug use Only 
{
    return m_wrist.Get();
}
void Claw::WristSetReadyPosition(float position)
{
    m_wristReadyPos = position;
}
float Claw::WristGetReadyPosition(void)
{
    return m_wristReadyPos;
}
bool Claw::WristGetHomed(void)
{
    return m_isWristHomed;
}
void Claw::WristSetHomed(bool homed)
{
    m_isWristHomed = homed;
}

float Claw::WristGetTemp(void)
{
    return m_wrist.GetMotorTemperature();
}
// bool  Claw::WristLimitSwitchForward(void)
// {
//     return m_wristFWDLimit.Get();
// }
// bool  Claw::WristLimitSwitchReverse(void)
// {
//     return m_wristREVLimit.Get();
// }
bool  Claw::WristLimitTop(void)
{
    return m_wristREVLimit.Get();
}