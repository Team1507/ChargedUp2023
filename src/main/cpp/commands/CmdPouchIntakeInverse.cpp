#include "commands/CmdPouchIntakeInverse.h"

CmdPouchIntakeInverse::CmdPouchIntakeInverse(Pouch *pouch, float power) 
{
  m_pouch = pouch;
  m_power = power;
  m_prevPower = 0;

}
void CmdPouchIntakeInverse::Initialize() 
{
  if(m_pouch->IntakeIsEnable2())
  {
    m_prevPower = m_pouch->IntakeGetPower(Pouch::WhatIntake::Outer);

    m_pouch->IntakeSetPower(m_power, Pouch::WhatIntake::Inverse);
  }
}


void CmdPouchIntakeInverse::Execute() {}


void CmdPouchIntakeInverse::End(bool interrupted) 
{
  if(m_pouch->IntakeIsEnable2())
  {
    m_pouch->IntakeSetPower(m_prevPower,Pouch::WhatIntake::Outer);
  }
  else
  {
    m_pouch->IntakeSetPower(0.0,Pouch::WhatIntake::Outer);
  }
}


bool CmdPouchIntakeInverse::IsFinished() 
{
  return false;
}
