if ((fd = open (path,
                  fl,
#ifdef O_BINARY
                  O_BINARY|
#endif
                  mode))
      < 0)
    return fnf_or_err_code_from_errno ();
