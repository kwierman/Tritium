#ifndef TriLogger_h_
#define TriLogger_h_

#include <boost/thread/mutex.hpp>

#include <string>
#include <iostream>     //for outputting to log files.
#include <fstream>      //"                          "

namespace Tritium{

  class TriLogger{
    public:
      static TriLogger* GetInstance();

      //Set the Log File
      void SetOutputFile(std::string);
      std::string GetOutputFile()
        {return fLogName;}

      template<typename T>
      TriLogger& operator << ( T input);
      template<typename T>
      TriLogger& operator()(T input);

      TriLogger& SetStatus(unsigned int status)
        {fCurrentStatus=(status>4?0:status);return *this;}

      enum{
        kHeader,        //0=Header
        kGood,          //1=Good Status
        kNormal,        //2=Normal Status.
        kWarning,       //3=Warning.
        kFail           //4=Fail
      };

    private:
      TriLogger();
      virtual ~TriLogger();
      TriLogger(const TriLogger&);                  // Prevent copy-construction
      TriLogger& operator=(const TriLogger&);       // Also blocking this operator.
      static TriLogger* fSingle;

      template<typename T>
      void Log(T input);                          // This is meant to be the actual logging function.

                                                  // Thread Safing measures.
      boost::mutex fLogMutex;                     // The Mutex for this Object.
      //boost::mutex::scoped_lock fLogLock;         // The Lock for the above mutex.

      std::string fLogName;                       // To Store the name of the log file.
      static const std::string fColors[6];        // To Store the output colors to the console.
      std::ofstream fLog;                         // to store the output log file.
      unsigned int fCurrentStatus;
  };

  static const std::string endl = "\n";
  
  TriLogger& TriLog(unsigned status=0);

  //static TriLogger* KRLog = TriLogger::GetInstance();//instantiate the singleton.
  //static TriLogger KRLog;//(*(TriLogger::GetInstance()));

  inline void TriLogger::SetOutputFile(std::string newName)
  {
    fLog.close();
    fLogName = newName;
    fLog.open(fLogName.c_str() );
  }

  template<typename T>
  inline TriLogger& TriLogger::operator << ( T input)
  {
    this->Log(input);
    return *(this);
  }

  template<typename T>
  inline TriLogger& TriLogger::operator()(T input)
  {
    this->Log(input);
    return *this;
  }

  //This is hopefully thread safe, so only certain functions can
  template<typename T>
  inline void TriLogger::Log(T input)
  {
    //fLogLock= boost::mutex::scoped_lock(fLogMutex);
    fLogMutex.lock();

    for(unsigned i=0; i<fCurrentStatus; i++)
    {
      std::cout<<"  ";
      fLog<<"  ";
    }

    if(fCurrentStatus!=2)
    {
      fLog<<input;
    }
    std::cout<<fColors[fCurrentStatus]<<input<<fColors[5];
    fLog.flush();
    fLogMutex.unlock();
    //fLogLock.unlock();
  }

} /* namespace KRAP */


#endif /* TriLogger_h_ */
