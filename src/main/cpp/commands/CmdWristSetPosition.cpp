#include "subsystems/Claw.h"
#include "commands/CmdWristSetPosition.h"


CmdWristSetPosition::CmdWristSetPosition(Claw *claw, float position) 
{
 m_claw = claw;
m_position = position;

}

// Called when the command is initially scheduled.
void CmdWristSetPosition::Initialize() 
{
  m_claw->WristSetPosition(m_position);
}
