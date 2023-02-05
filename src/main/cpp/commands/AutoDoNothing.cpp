 #include "commands/AutoDoNothing.h"
 #include "commands/Autos.h"
 #include "commands/CmdPrintText.h"
 #include "commands/CmdDriveClearAll.h"

 AutoDoNothing::AutoDoNothing(Drivetrain *drivetrain)
 {
   AddCommands(

    //Auto Setup 
    CmdPrintText("****** AutoDoNothing ******"),
    CmdDriveClearAll(drivetrain),


    CmdPrintText("AutoDoNothing Complete")
   );

 }
