if (CHECK_FLAG('4'))
		af = AF_INET;
#ifdef INET6
	else if (CHECK_FLAG('6'))
		af = AF_INET6;
#endif
