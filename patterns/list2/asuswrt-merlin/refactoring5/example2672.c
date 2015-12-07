#ifdef HAVE_TERMIOS_H
if(tcgetattr(outfd, &orig) != 0)
  {
    perror("tcgetattr");
  }
