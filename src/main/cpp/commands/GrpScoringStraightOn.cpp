#include "commands/GrpScoringStraightOn.h"
#include "commands/CmdArmLevelSetPosition.h"
#include "commands/CmdArmExtensionSetPosition.h"
#include "commands/CmdTurretTurn2Angle.h"
#include "commands/CmdClawSetOuttakePower.h"
#include "commands/CmdWristSetPosition.h"
#include "commands/CmdPrintText.h"
#include "frc2/command/WaitCommand.h"
//enum ScoringStraightPosition{MidCone, MidCube, HighCone, HighCube};
//ArmLevel{Level_Pouch, Low, Mid, High};

#define TicksPerAngle (-159.0/90.0)

#define Ticks2Angle(ticks) (ticks / TicksPerAngle) 
#define Angle2Ticks(angle) (angle * TicksPerAngle)


typedef struct
{
  bool  extension;
  float wristAngle;
  float outtakePower;
  ArmLevel armLevel;
} scoringStraightPosition_t;
                                                                            //(Encoder)
                                                            // extension,    wristAngle,        outtakePower,   armLevel
scoringStraightPosition_t scoringStraightPositionTable[] = {{false,        15.0,                -0.8,           ArmLevel::Mid         }, //MidCone
                                                            {false,        15.0,                -0.4,           ArmLevel::Mid         }, //MidCube
                                                            {true ,        17.5,                -0.8,           ArmLevel::High        }, //HighCone
                                                            {true,        20.0,                -0.4,           ArmLevel::High        }};//HighCube
                
GrpScoringStraightOn::GrpScoringStraightOn(Arm *arm, Claw *claw, Pouch *pouch ,ScoringStraightPosition scoringStraightPosition) 
{
  AddCommands(
    CmdArmLevelSetPosition(arm, scoringStraightPositionTable[scoringStraightPosition].armLevel, pouch),
    CmdWristSetPosition(claw, scoringStraightPositionTable[scoringStraightPosition].wristAngle),
    frc2::WaitCommand(1.0_s),
    CmdArmExtensionSetPosition(arm, scoringStraightPositionTable[scoringStraightPosition].extension),
    CmdClawSetOuttakePower(claw, scoringStraightPositionTable[scoringStraightPosition].outtakePower),
    CmdPrintText("Straight Scoring Done")
  );
  //scoringStraightPositionTable[scoringPosition].outtakePower
  // CmdArmLevelSetPosition(arm, scoringPositionTable[scoringPosition].armLevel,pouch),
  // CmdArmExtensionSetPosition(arm, scoringPositionTable[scoringPosition].extension),
  // CmdTurretTurn2Angle(arm, scoringPositionTable[scoringPosition].turretAngle),
  // CmdWristSetPosition(claw, scoringPositionTable[scoringPosition].wristAngle),
  // CmdClawSetOuttakePower(claw, scoringPositionTable[scoringPosition].outtakePower)
  
}