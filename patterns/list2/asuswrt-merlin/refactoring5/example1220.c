#  ifdef HAVE_TERMIO_H
if(ioctl(outfd, TCGETA, &orig) != 0)
  {
    perror("ioctl");
  }
