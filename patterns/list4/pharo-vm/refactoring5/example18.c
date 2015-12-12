#ifdef WIN32
if (writefn_win32 != NULL) {
    make_image_win32 (sectors, filename, writefn_win32);
  }
  else
#endif
  {
    make_image (sectors, filename, write_function);
  }
