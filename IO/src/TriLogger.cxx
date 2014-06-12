/*
 * TriLogger.cxx
 *
 *  Created on: Nov 2, 2012
 *      Author: kjw
 */

#include "TriLogger.h"

namespace Tritium
{

  const std::string TriLogger::fColors[6]={"\033[95m","\033[94m","\033[92m","\033[93m","\033[91m","\033[0m"};
  

   TriLogger& TriLog(unsigned status)
  {
    TriLogger::GetInstance()->SetStatus(status);
    return *(TriLogger::GetInstance());
  }

  TriLogger* TriLogger::fSingle=NULL;

  //this needs to prepare all
  TriLogger::TriLogger()
  {
    fLogName ="TritiumLog.log";
    fLog.open(fLogName.c_str());
    fCurrentStatus=0;//default to the header setting.
  }

  TriLogger::~TriLogger()
  {
    fLog.close();
  }

  inline TriLogger* TriLogger::GetInstance()
  {
    if(!fSingle)
      fSingle=new TriLogger();
    return fSingle;
  }

}