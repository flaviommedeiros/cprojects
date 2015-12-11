#if alpha || Linux_ppc
if (ioctl(fd,_IO(x, y), addr))
#else
  if (ioctl(fd,IOC_VOID | (size<<16) | (x<<8) | y, addr))
#endif
     return(makeint(-errno));
  else return(T);
