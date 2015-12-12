#ifdef EAI_SYSTEM
if (code == EAI_SYSTEM)
    e = err_code_from_errno ();
  else
#endif

    e = ___GAI_CODE_ERR(code);
