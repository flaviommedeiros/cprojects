#if alpha
if (ioctl(fd,_IOC(IOC_OUT, x, y, size), addr))
#else
  if (ioctl(fd,IOC_OUT | (size<<16) | (x<<8) | y, addr))
#endif
    return(makeint(-errno));
  else return(T);
