#pragma once

#include <frc2/command/SubsystemBase.h>
#include "CTRE/Phoenix.h"
#include "rev/CANSparkMax.h"
#include "Constants.h"
#include <frc/DoubleSolenoid.h>
#include <frc/PneumaticsModuleType.h>
#include <frc/DigitalInput.h>
#include "subsystems/Pouch.h"

// #define TURRET

enum ArmLevel{Level_Pouch, Low, Mid, High};
class Arm : public frc2::SubsystemBase 
{
 public:
  Arm(Pouch *pouch);
  void Periodic() override;
  #ifdef TURRET
  //**********************************Turret******************************
  void  TurretTurn2Angle(float angle);
  void  TurretSetPower(float power);
  void  TurretSetEncoder(float encoder);
  
  float TurretGetPower(void);
  float TurretGetAngle(void);
  float TurretGetEncoder(void);
  bool  TurretGetLeftLimitSW(void); 
  bool  TurretGetRightLimitSW(void);
  #endif
  //***********************************ARM*********************************
  void  ElevationArmSetPosition(ArmLevel position);
  void  ExtensionSetPosition(bool position);
  void  AirSpringSetPosition(bool position);
  bool  ElevationHomeLimitSwitch(void);
  ArmLevel ElevationArmGetPosition(void);

 private:
  frc::DigitalInput m_elevationHomeLimitSwitch{DIO_ELEVATION_HOME_LIMIT_SWITCH_ID};

  #ifdef TURRET
  rev::CANSparkMax             m_turret {CAN_TURRET_ID, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::SparkMaxRelativeEncoder m_turretEncoder = m_turret.GetEncoder();
  rev::SparkMaxPIDController   m_turretPID = m_turret.GetPIDController();
  rev::SparkMaxLimitSwitch     m_turretFWDLimit = m_turret.GetForwardLimitSwitch(rev::SparkMaxLimitSwitch::Type::kNormallyOpen);
  rev::SparkMaxLimitSwitch     m_turretREVLimit = m_turret.GetReverseLimitSwitch(rev::SparkMaxLimitSwitch::Type::kNormallyOpen);

  int m_wanted_position;
  bool m_limitPressed;  
  #endif

  frc::DoubleSolenoid          m_lowerArm {CAN_PCM2_ID, frc::PneumaticsModuleType::CTREPCM, PCM_LOWER_ARM_EXTEND_ID, PCM_LOWER_ARM_RETRACT_ID};
  frc::DoubleSolenoid          m_upperArm {CAN_PCM2_ID, frc::PneumaticsModuleType::CTREPCM, PCM_UPPER_ARM_EXTEND_ID, PCM_UPPER_ARM_RETRACT_ID};
  frc::DoubleSolenoid          m_armExtension {CAN_PCM2_ID, frc::PneumaticsModuleType::CTREPCM, PCM_ARM_EXTENSION_EXTEND_ID, PCM_ARM_EXTENSION_RETRACT_ID};

  frc::DoubleSolenoid          m_airSpring {CAN_PCM2_ID, frc::PneumaticsModuleType::CTREPCM,  PCM_AIR_SPRING_EXTEND_ID, PCM_AIR_SPRING_RETRACT_ID}; // WRITE CODE FOR LATER THING
  
  Pouch *m_pouch;

};