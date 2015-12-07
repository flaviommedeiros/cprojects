if (width < 0 || height < 0) {
#endif
		term_deinit_int();
		term_init_int();
#ifdef HAVE_CURSES_RESIZETERM
	} else if (term_width != width || term_height != height) {
		term_width = width;
		term_height = height;
                resizeterm(term_height, term_width);
	}
#endif
