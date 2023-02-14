#include "commands/GrpScoringSetPosition.h"
#include "commands/CmdArmLevelSetPosition.h"
#include "commands/CmdArmExtensionSetPosition.h"
#include "commands/CmdTurretTurn2Angle.h"
#include "commands/CmdClawSetOuttakePower.h"
#include "commands/CmdWristSetPosition.h"
//ScoringPosition{Home, Ready, HighLeft, HighShelf, HighRight, MidLeft, MidShelf, MidRight};
//ArmLevel{Level_Pouch, Low, Mid, High};

typedef struct
{
  float turretAngle; 
  bool  extension;
  float wristAngle;
  float outtakePower;
  ArmLevel armLevel;
} scoringPosition_t;

                                           //TurretAngle, extension,    wristAngle,        outtakePower,   armLevel
scoringPosition_t scoringPositionTable[] = {{0,           false,        0,                 0,              ArmLevel::Level_Pouch},
                                            {0,           false,        0,                 0,              ArmLevel::Low        },
                                            {55,          true,         0,                 0,              ArmLevel::High       },
                                            {90,          true,         0,                 0,              ArmLevel::High       },
                                            {135,         true,         0,                 0,              ArmLevel::High       },
                                            {55,          false,        0,                 0,              ArmLevel::Mid        },
                                            {90,          false,        0,                 0,              ArmLevel::Mid        },
                                            {135,         false,        0,                 0,              ArmLevel::Mid        }};
 
GrpScoringSetPosition::GrpScoringSetPosition(Arm *arm, Claw *claw, ScoringPosition scoringPosition) 
{
  AddCommands(
  CmdArmLevelSetPosition(arm, scoringPositionTable[scoringPosition].armLevel),
  CmdArmExtensionSetPosition(arm, scoringPositionTable[scoringPosition].extension),
  CmdTurretTurn2Angle(arm, scoringPositionTable[scoringPosition].turretAngle),
  CmdWristSetPosition(claw, scoringPositionTable[scoringPosition].wristAngle),
  CmdClawSetOuttakePower(claw, scoringPositionTable[scoringPosition].outtakePower)
  );
}