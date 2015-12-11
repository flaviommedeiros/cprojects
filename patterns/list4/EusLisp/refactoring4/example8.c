#if alpha || Linux_ppc
if (ioctl(fd,_IOC(IOC_INOUT, x, y, size), addr))
#else
  if (ioctl(fd,IOC_INOUT | (size <<16) | (x<<8) | y, addr))
#endif
    return(makeint(-errno)) ;
  else return(T);
