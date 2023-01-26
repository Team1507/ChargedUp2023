#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>

class CmdPrintText
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 CmdPrintText> {
 public:
  CmdPrintText(std::string text);

  void Initialize() override;

 private:
  std::string m_text;

};
