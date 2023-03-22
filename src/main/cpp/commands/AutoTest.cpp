#include "commands/AutoTest.h"
#include "commands/CmdDriveStraightVelocity.h"
#include "commands/CmdGyroSetAngleOffset.h"
#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStop.h"
#include "frc2/command/WaitCommand.h"

AutoTest::AutoTest(Drivetrain *drivetrain) 
{
    AddCommands
    (
        CmdDriveClearAll(drivetrain),
        CmdGyroSetAngleOffset(drivetrain, 180),
        CmdDriveStraightVelocity(drivetrain, .3, 10, 0, 24, false, false, 0.0),
        CmdDriveStraightVelocity(drivetrain, .4, -1.5, 180, 128, false, false, 0.0),
        CmdDriveStraightVelocity(drivetrain, .3, 3.5, 180, 24, false, true, 0.0),
        frc2::WaitCommand(1.0_s),
        CmdDriveStraightVelocity(drivetrain, .4, 170, 360, 160, false, true, 0.0),
        CmdDriveStop(drivetrain)
    );
}
