#include "commands/GrpScoringSetPosition.h"
#include "commands/CmdArmLevelSetPosition.h"
#include "commands/CmdArmExtensionSetPosition.h"
#include "commands/CmdTurretSetAngle.h"
#include "commands/CmdWristSetPosition.h"
//ScoringPosition{Home, Ready, HighLeft, HighShelf, HighRight, MidLeft, MidShelf, MidRight};
//ArmLevel{Level_Pouch, Low, Mid, High};

typedef struct
{
  float turretAngle;
  bool  extension;
  float wristAngle;
  ArmLevel armLevel;

} scoringPosition_t;


scoringPosition_t scoringPositionTable[] = {{0, false, 0, ArmLevel::Level_Pouch},
                                            {0, false, 0, ArmLevel::Low  },
                                            {0, false, 0, ArmLevel::High },
                                            {0, false, 0, ArmLevel::High },
                                            {0, false, 0, ArmLevel::High },
                                            {0, false, 0, ArmLevel::Mid  },
                                            {0, false, 0, ArmLevel::Mid  },
                                            {0, false, 0, ArmLevel::Mid  }};

GrpScoringSetPosition::GrpScoringSetPosition(Arm *arm, Claw *claw, ScoringPosition scoringPosition) 
{
  AddCommands(
  CmdArmLevelSetPosition(arm, scoringPositionTable[scoringPosition].armLevel),
  CmdArmExtensionSetPosition(arm, scoringPositionTable[scoringPosition].extension),
  CmdTurretSetAngle(arm, scoringPositionTable[scoringPosition].turretAngle),
  CmdWristSetPosition(claw, scoringPositionTable[scoringPosition].wristAngle)
  );
}
