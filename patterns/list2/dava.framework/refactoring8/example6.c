TRIO_STRING_PUBLIC TRIO_CONST char *
trio_error
TRIO_ARGS1((error_number),
	   int error_number)
{
#if defined(USE_STRERROR)
  
  return strerror(error_number);

#elif defined(USE_SYS_ERRLIST)

  extern char *sys_errlist[];
  extern int sys_nerr;

  return ((error_number < 0) || (error_number >= sys_nerr))
    ? "unknown"
    : sys_errlist[error_number];
 
#else
  
  return "unknown";
  
#endif
}
