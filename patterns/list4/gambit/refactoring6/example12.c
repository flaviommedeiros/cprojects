if (d->input_raw
#ifdef USE_LINEEDITOR
            || d->lineeditor_mode != LINEEDITOR_MODE_DISABLE
#endif
            )
          {
            new_termios.c_iflag &= ~(IMAXBEL
                                     | ISTRIP
                                     | ICRNL
                                     | INLCR
                                     | IGNCR
                                     | ICRNL
                                     | IXON
                                     | IXOFF
#ifdef IUCLC
                                     | IUCLC
#endif
                                     );
            new_termios.c_iflag &= ~(ICRNL);
            new_termios.c_lflag &= ~(ICANON | ECHO | ECHOCTL);

#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE 0xff
#endif

#if 0
            new_termios.c_cc[VEOF]     = _POSIX_VDISABLE;
            new_termios.c_cc[VEOL]     = _POSIX_VDISABLE;
            new_termios.c_cc[VEOL2]    = _POSIX_VDISABLE;
            new_termios.c_cc[VERASE]   = _POSIX_VDISABLE;
            new_termios.c_cc[VWERASE]  = _POSIX_VDISABLE;
            new_termios.c_cc[VKILL]    = _POSIX_VDISABLE;
            new_termios.c_cc[VREPRINT] = _POSIX_VDISABLE;
            new_termios.c_cc[VINTR]    = _POSIX_VDISABLE;
            new_termios.c_cc[VQUIT]    = _POSIX_VDISABLE;
            new_termios.c_cc[VSUSP]    = _POSIX_VDISABLE;
#endif
#ifdef VDSUSP
            new_termios.c_cc[VDSUSP]   = _POSIX_VDISABLE;
#endif
#if 0
            new_termios.c_cc[VSTART]   = _POSIX_VDISABLE;
            new_termios.c_cc[VSTOP]    = _POSIX_VDISABLE;
#endif
#ifdef VLNEXT
            new_termios.c_cc[VLNEXT]   = _POSIX_VDISABLE;
#endif
#if 0
            new_termios.c_cc[VDISCARD] = _POSIX_VDISABLE;
            new_termios.c_cc[VMIN]     = _POSIX_VDISABLE;
            new_termios.c_cc[VTIME]    = _POSIX_VDISABLE;
            new_termios.c_cc[VSTATUS]  = _POSIX_VDISABLE;
#endif

            new_termios.c_cc[VMIN]     = 1;
            new_termios.c_cc[VTIME]    = 0;
          }
        else
          {
            new_termios.c_iflag |= (ICRNL);
            new_termios.c_lflag |= (ICANON | ECHO | ECHOCTL);
          }
