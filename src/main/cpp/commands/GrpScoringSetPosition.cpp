#include "commands/GrpScoringSetPosition.h"
#include "commands/CmdArmLevelSetPosition.h"
#include "commands/CmdArmExtensionSetPosition.h"
#include "commands/CmdTurretSetAngle.h"
//ScoringPosition{Home, Ready, HighLeft, HighShelf, HighRight, MidLeft, MidShelf, MidRight};
//ArmLevel{Level_Pouch, Low, Mid, High};

typedef struct
{
  float turretAngle;
  bool  extension;
  ArmLevel armLevel;

} scoringPosition_t;


scoringPosition_t scoringPositionTable[] = {{0, false, ArmLevel::Level_Pouch},
                                            {0, false, ArmLevel::Low  },
                                            {0, false, ArmLevel::High },
                                            {0, false, ArmLevel::High },
                                            {0, false, ArmLevel::High },
                                            {0, false, ArmLevel::Mid  },
                                            {0, false, ArmLevel::Mid  },
                                            {0, false, ArmLevel::Mid  }};

GrpScoringSetPosition::GrpScoringSetPosition(Arm *arm, ScoringPosition scoringPosition) 
{
  AddCommands(
  CmdArmLevelSetPosition(arm, scoringPositionTable[scoringPosition].armLevel),
  CmdArmExtensionSetPosition(arm, scoringPositionTable[scoringPosition].extension),
  CmdTurretSetAngle(arm, scoringPositionTable[scoringPosition].turretAngle)
  );
}
