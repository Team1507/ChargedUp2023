 #include "commands/AutoDoNothing.h"
 #include "commands/CmdPrintText.h"
 #include "commands/CmdDriveClearAll.h"
 #include "commands/CmdDriveStop.h"
 #include "commands/CmdGyroSetAngleOffset.h"

 AutoDoNothing::AutoDoNothing(Drivetrain *drivetrain)
 {
   AddCommands(

    //Auto Setup 
    CmdPrintText("****** AutoDoNothing ******"),
    CmdDriveClearAll(drivetrain),
    CmdGyroSetAngleOffset(drivetrain, 180.0),
    CmdDriveStop(drivetrain), // just incase 

            
    CmdPrintText("AutoDoNothing Complete")
   );

 }
