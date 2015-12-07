#  ifdef HAVE_TERMIO_H
if(ioctl(outfd, TCSETA, &orig) != 0)
  {
    perror("ioctl");
  }
