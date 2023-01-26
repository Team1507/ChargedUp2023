#include "commands/CmdPrintText.h"
#include <iostream>


CmdPrintText::CmdPrintText(std::string text) 
{
  m_text = text;
}

void CmdPrintText::Initialize() 
{  
 std::cout << m_text << std::endl; 
}
