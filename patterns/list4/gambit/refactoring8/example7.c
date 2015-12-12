___SCMOBJ ___err_code_from_GetLastError_debug
   ___P((int lineno,
         char *file),
        (lineno,
         file)
int lineno;
char *file;)
#else
___SCMOBJ ___err_code_from_GetLastError ___PVOID
#endif
{
  DWORD e = GetLastError ();

#ifdef ___DEBUG
  char buf[___ERR_MAX_LENGTH+1];
  DWORD len = FormatMessageA
                (FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_MAX_WIDTH_MASK,
                 NULL,
                 e,
                 MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
                 buf,
                 ___ERR_MAX_LENGTH,
                 NULL);
  ___printf ("*** OS ERROR AT \"%s\"@%d.1 -- GetLastError=%d (%s)\n",
             file,
             lineno,
             ___CAST(int,e),
             buf);
#endif

  if (e == NO_ERROR)
    return ___FIX(___UNKNOWN_ERR);

  if (e == ERROR_FILE_NOT_FOUND || e == ERROR_PATH_NOT_FOUND)
    return ___ERR_CODE_ENOENT;

  return ___FIX(___WIN32_ERR(e));
}
