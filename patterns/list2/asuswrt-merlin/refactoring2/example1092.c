#if VEOF == VMIN
if ((mode->c_lflag & ICANON) == 0)
#endif
		wrapf("min = %u; time = %u;", mode->c_cc[VMIN], mode->c_cc[VTIME]);
