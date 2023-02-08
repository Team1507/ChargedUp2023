#include "commands/CmdPouchIntakeSetPower.h"


CmdPouchIntakeSetPower::CmdPouchIntakeSetPower(Pouch *pouch, Pouch::WhatIntake type, float power) 
{
  m_pouch = pouch;
  m_type = type;
  m_power = power;
}


void CmdPouchIntakeSetPower::Initialize() 
{
  m_pouch->IntakeSetPower(m_power, m_type);
}
