#include "commands/AutoTest.h"
#include "commands/CmdDriveStraightVelocity.h"
#include "commands/CmdGyroSetAngleOffset.h"
#include "commands/CmdDriveClearAll.h"
#include "commands/CmdDriveStop.h"

AutoTest::AutoTest(Drivetrain *drivetrain) 
{
    AddCommands
    (
        CmdDriveClearAll(drivetrain),
        CmdGyroSetAngleOffset(drivetrain, 180),
        CmdDriveStraightVelocity(drivetrain, .3, 4, -180, 140, false, true, 0.0),
        CmdDriveStop(drivetrain)
    );
}
