___SCMOBJ ___os_path_homedir ___PVOID
{
  ___SCMOBJ e;
  ___SCMOBJ result;
  ___UCS_2STRING cstr1;

  static ___UCS_2 cvar1[] =
  { 'H', 'O', 'M', 'E', '\0' };

  if ((e = ___getenv_UCS_2 (cvar1, &cstr1)) != ___FIX(___NO_ERR))
    result = e;
  else
    {
      if (cstr1 != 0)
        {
          CANONICALIZE_PATH(___UCS_2STRING, cstr1);

          if ((e = ___UCS_2STRING_to_SCMOBJ
                     (___PSTATE,
                      cstr1,
                      &result,
                      ___RETURN_POS))
              != ___FIX(___NO_ERR))
            result = e;
          else
            ___release_scmobj (result);

          ___free_mem (cstr1);
        }
      else
        {
#ifdef USE_WIN32

          ___CHAR_TYPE(___PATH_CE_SELECT) homedir[___PATH_MAX_LENGTH+1];
          int len = ___PATH_MAX_LENGTH+1;
          int n;

          static ___CHAR_TYPE(___GETENV_CE_SELECT) cvar2[] =
          { 'H', 'O', 'M', 'E', 'D', 'R', 'I', 'V', 'E', '\0' };

          static ___CHAR_TYPE(___GETENV_CE_SELECT) cvar3[] =
          { 'H', 'O', 'M', 'E', 'P', 'A', 'T', 'H', '\0' };

          n = GetEnvironmentVariable (cvar2, homedir, len);

          if (n > 0 && n < len)
            {
              len -= n;

              n = GetEnvironmentVariable (cvar3, homedir+n, len);

              if (n > 0 && n < len)
                {
                  CANONICALIZE_PATH(___STRING_TYPE(___PATH_CE_SELECT), homedir);

                  if ((e = ___NONNULLSTRING_to_SCMOBJ
                             (___PSTATE,
                              homedir,
                              &result,
                              ___RETURN_POS,
                              ___CE(___PATH_CE_SELECT)))
                      != ___FIX(___NO_ERR))
                    result = e;
                  else
                    ___release_scmobj (result);
                }
              else
                result = ___FAL;
            }
          else
            result = ___FAL;

#else

          result = ___FAL;

#endif
        }
    }

  return result;
}
