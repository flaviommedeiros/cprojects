___SCMOBJ ___os_user_name ___PVOID
{
  ___SCMOBJ e;
  ___SCMOBJ result;
  ___UCS_2STRING cstr;

#ifdef USE_WIN32

  static ___UCS_2 cvar[] =
  { 'U', 'S', 'E', 'R', 'N', 'A', 'M', 'E', '\0' };

#else

  static ___UCS_2 cvar[] =
  { 'U', 'S', 'E', 'R', '\0' };

#endif

  if ((e = ___getenv_UCS_2 (cvar, &cstr)) != ___FIX(___NO_ERR))
    result = e;
  else
    {
      if ((e = ___UCS_2STRING_to_SCMOBJ
                 (___PSTATE,
                  cstr,
                  &result,
                  ___RETURN_POS))
          != ___FIX(___NO_ERR))
        result = e;
      else
        ___release_scmobj (result);

      if (cstr != 0)
        ___free_mem (cstr);
    }

  return result;
}
