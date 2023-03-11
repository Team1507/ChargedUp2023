 #include "commands/AutoDoNothing.h"
 #include "commands/CmdPrintText.h"
 #include "commands/CmdDriveClearAll.h"
 #include "commands/CmdDriveStop.h"

 AutoDoNothing::AutoDoNothing(Drivetrain *drivetrain)
 {
   AddCommands(

    //Auto Setup 
    CmdPrintText("****** AutoDoNothing ******"),
    CmdDriveClearAll(drivetrain),
    CmdDriveStop(drivetrain), // just incase 


    CmdPrintText("AutoDoNothing Complete")
   );

 }
