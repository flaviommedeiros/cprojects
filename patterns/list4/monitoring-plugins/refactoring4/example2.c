#  if HAVE_GETEGID
if (getegid () != saved_gid)
    abort ();
