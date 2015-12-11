#  if HAVE_GETEGID
if (getegid () != gid)
    abort ();
