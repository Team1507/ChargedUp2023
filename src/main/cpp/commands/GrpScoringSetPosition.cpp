#include "commands/GrpScoringSetPosition.h"
#include "commands/CmdArmLevelSetPosition.h"
#include "commands/CmdArmExtensionSetPosition.h"
#include "commands/CmdTurretTurn2Angle.h"
#include "commands/CmdClawSetOuttakePower.h"
#include "commands/CmdWristSetPosition.h"
#include "commands/CmdPrintText.h"
#include "frc2/command/WaitCommand.h"
//ScoringPosition{Home, Ready, HighLeft, HighShelf, HighRight, MidLeft, MidShelf, MidRight};
//ArmLevel{Level_Pouch, Low, Mid, High};

#define TicksPerAngle (-159.0/90.0)

#define Ticks2Angle(ticks) (ticks / TicksPerAngle) 
#define Angle2Ticks(angle) (angle * TicksPerAngle)


typedef struct
{
  float turretAngle; 
  bool  extension;
  float wristAngle;
  float outtakePower;
  ArmLevel armLevel;
} scoringPosition_t;
                                                                      //(Encoder)
                                           //TurretAngle, extension,    wristAngle,        outtakePower,   armLevel
scoringPosition_t scoringPositionTable[] = {{0,           false,        0,                 0,              ArmLevel::Level_Pouch},//Home
                                            {0,           false,        0,                 0,              ArmLevel::Low        },//Ready
                                            {71,          true,         24,                -0.4,           ArmLevel::High       },//HighLeft
                                            {94,          false,         2,                -0.6,           ArmLevel::Mid        },//HighShelf
                                            {113,         true,         24,                -0.4,           ArmLevel::High       },//HighRight
                                            {62,          false,        19.3,              -0.4,           ArmLevel::Mid        },//MidLeft
                                            {94,          false,        35,                -0.3,           ArmLevel::Mid        },//MidShelf
                                            {124,         false,        19.3,              -0.4,           ArmLevel::Mid        }};//MidRigft
 
GrpScoringSetPosition::GrpScoringSetPosition(Arm *arm, Claw *claw, Pouch *pouch ,ScoringPosition scoringPosition) 
{
  AddCommands(
  frc2::SequentialCommandGroup
    {
      CmdArmLevelSetPosition(arm, ArmLevel::Mid, pouch),
      CmdPrintText("Group Scoring"),
      frc2::WaitCommand(1.0_s),
      frc2::ParallelCommandGroup
      {
        CmdArmLevelSetPosition(arm, scoringPositionTable[scoringPosition].armLevel, pouch),
        CmdArmExtensionSetPosition(arm, false),
        CmdWristSetPosition(claw, 13),
        CmdClawSetOuttakePower(claw, scoringPositionTable[scoringPosition].outtakePower),
        CmdTurretTurn2Angle(arm, (scoringPositionTable[scoringPosition].turretAngle))
      },

      CmdArmExtensionSetPosition(arm, scoringPositionTable[scoringPosition].extension),
      CmdWristSetPosition(claw, scoringPositionTable[scoringPosition].wristAngle),
      
    },
  CmdPrintText("Scoring Done")
  );
  // CmdArmLevelSetPosition(arm, scoringPositionTable[scoringPosition].armLevel,pouch),
  // CmdArmExtensionSetPosition(arm, scoringPositionTable[scoringPosition].extension),
  // CmdTurretTurn2Angle(arm, scoringPositionTable[scoringPosition].turretAngle),
  // CmdWristSetPosition(claw, scoringPositionTable[scoringPosition].wristAngle),
  // CmdClawSetOuttakePower(claw, scoringPositionTable[scoringPosition].outtakePower)
  
}