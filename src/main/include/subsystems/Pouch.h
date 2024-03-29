#pragma once
#include "rev/CANSparkMax.h"
#include "Constants.h"
#include <frc2/command/SubsystemBase.h>
#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>
#include <frc/PneumaticsModuleType.h>
#include "ctre/Phoenix.h"
#include <frc/PowerDistribution.h>

// #define INNER_INTAKE
#ifdef INNER_INTAKE
#define INNER_INTAKE_POWER 0.5
#define INNER_INTAKE_CURRENT_LIMIT 1.5
#define INNER_INTAKE_TICKS_TO_REV  102
#endif

#define OUTER_INTAKE_RETRACT_DELAY 1000/20 //ms /20ms 

class Pouch : public frc2::SubsystemBase {
 public:
  Pouch(frc::PowerDistribution *pdh);
  
  enum WhatIntake {Inner,Outer,Inverse};

  #ifdef INNER_INTAKE
  void InnerIntakeSetPosition(float position);
  void InnerIntakeTurnToPosition(float position);
  int  InnerIntakeGetEncoder(void);
  // void InnerIntakeTurnOnce(void);  
  #endif

  void IntakeSetPower(float power,WhatIntake type);
  double IntakeGetPower(WhatIntake type);
  void IntakeEnable(bool enable);
  bool IntakeIsEnable(void);

  void IntakeEnable2(bool enable);
  bool IntakeIsEnable2(void);

  void IntakeDeploy(void);
  void IntakeRetract(void);

  void IntakeDeployHalf(void);
  void IntakeRetractHalf(void);

  bool IntakeIsDeployed(void);

  bool IntakeIsDeployedHalf(void);

  void SetRampPosition(bool deploy);
  bool ReadSensorState(void);
  
  void Periodic() override;
  double IntakeGetCurrent(void);
  void OuterIntakeClose();
  void OuterIntakeOpen();

 private:
  #ifdef INNER_INTAKE
  rev::CANSparkMax m_inner {CAN_POUCH_INNER_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::SparkMaxRelativeEncoder m_innerEncoder = m_inner.GetEncoder();
  rev::SparkMaxPIDController   m_innerPIDController = m_inner.GetPIDController();
  #endif

  rev::CANSparkMax m_outerLeft {CAN_POUCH_OUTER_LEFT_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_outerRight {CAN_POUCH_OUTER_RIGHT_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

  frc::DoubleSolenoid m_OuterIntake {CAN_PCM1_ID, frc::PneumaticsModuleType::CTREPCM, PCM_OUTER_INTAKE_DEPLOY_ID, PCM_OUTER_INTAKE_RETRACT_ID};
  frc::DoubleSolenoid m_ramp        {CAN_PCM1_ID, frc::PneumaticsModuleType::CTREPCM, PCM_RAMP_DEPLOY_ID, PCM_RAMP_RETRACT_ID};
  frc::DoubleSolenoid m_outerIntakeClose {CAN_PCM1_ID, frc::PneumaticsModuleType::CTREPCM, PCM_OUTER_INTAKE_CLOSE_ID, PCM_OUTER_INTAKE_OPEN_ID};
  frc::DoubleSolenoid m_outerIntakeHalf {CAN_PCM1_ID, frc::PneumaticsModuleType::CTREPCM, PCM_OUTER_INTAKE_HALF_EXTEND_ID, PCM_OUTER_INTAKE_HALF_RETRACT_ID};

  frc::DigitalInput m_gamePieceDetect{DIO_POUCH_DETECT_ID};
  frc::PowerDistribution *m_pdh;
  bool m_isIntaking;
  bool m_isIntaking2;
};
