___HIDDEN const char *h_errno_to_string
   ___P((int code),
        (code)
int code;)
{
#ifdef USE_hstrerror

  return hstrerror (code);

#else

  static char *h_errno_messages[] =
  {
    "Resolver Error 0 (no error)",
    "Unknown host",
    "Host name lookup failure",
    "Unknown server error",
    "No address associated with name"
  };

  if (code >= 0 && code <= 4)
    return h_errno_messages[code];

  return "Unknown resolver error";

#endif
}
