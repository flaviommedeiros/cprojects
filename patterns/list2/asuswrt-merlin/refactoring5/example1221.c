#ifdef HAVE_TERMIOS_H
if(tcsetattr(outfd, TCSAFLUSH, &orig) != 0)
  {
    perror("tcgetattr");
  }
