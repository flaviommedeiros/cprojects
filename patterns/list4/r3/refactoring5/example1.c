#ifndef HAS_SMART_CONSOLE
if (isatty(Std_Inp))
			Term_IO = Init_Terminal();
		else
#endif
			Term_IO = 0;
