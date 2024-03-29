#include "subsystems/Arm.h"
#include "subsystems/Claw.h"
#include "subsystems/Pouch.h"
#include "subsystems/DriverFeedback.h"
#include "subsystems/Toperator.h"
#include "subsystems/Camera.h"
#include "frc/XboxController.h"
#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>


#include "commands/GrpScoringSetPosition.h"
#include "commands/GrpScoringStraightOn.h"
#include "commands/GrpReturnToPouch.h"
#include "commands/GrpAllFindHome.h"
#include "commands/CmdClawEject.h"
#include "commands/CmdClawIntakeEnable.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */

//Camera *camera,
class CmdToperatorDefault
    : public frc2::CommandHelper<frc2::CommandBase, CmdToperatorDefault> {
 public:
  CmdToperatorDefault(Toperator *toperator, frc::XboxController *topDriver, Claw *claw, Arm *arm, Pouch *pouch,  DriverFeedback *driverfeedback);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    Toperator *m_toperator;
    frc::XboxController *m_topDriver;
    Claw *m_claw;
    Arm *m_arm;
    Pouch *m_pouch;
    DriverFeedback *m_driverFeedback;
    //Camera *m_camera;

    bool m_isIntaking;
    bool m_isOuttaking;
    bool m_isDpadCenter;
    bool m_isInnerIntaking; 
    bool m_isOuterIntaking;
    bool m_isOuterIntakeClosed;
    bool m_isRampActivated;
    bool m_isTurret;
    bool m_wristManualOverride;
    bool m_isOuterIntakeDeployed;
    bool m_wristHome;
    bool m_isLowShot;

  

    //ScoringPosition{Home, Ready, HighLeft, HighShelf, HighRight, MidLeft, MidShelf, MidRight};

    GrpScoringSetPosition *m_scoringHome;
    GrpScoringSetPosition *m_scoringReady;
    GrpScoringSetPosition *m_scoringHighLeft;
    GrpScoringSetPosition *m_scoringHighShelf;
    GrpScoringSetPosition *m_scoringHighRight;
    GrpScoringSetPosition *m_scoringMidLeft;
    GrpScoringSetPosition *m_scoringMidShelf;
    GrpScoringSetPosition *m_scoringMidRight;

    GrpScoringStraightOn  *m_scoringMidCone;
    GrpScoringStraightOn  *m_scoringMidCube;
    GrpScoringStraightOn  *m_scoringHighCone;
    GrpScoringStraightOn  *m_scoringHighCube;
    

    GrpAllFindHome        *m_findHome;

    GrpReturnToPouch      *m_returnToPouch;

    CmdClawEject          *m_clawEject;


};
