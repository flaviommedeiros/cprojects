#if defined(__NTVIS__)
if( GetThreadTimes(phd, &CreateTime, &ExitTime, &KernelTime, &UserTime) 
      != TRUE) 
#else
  phd = GetCurrentProcess();
