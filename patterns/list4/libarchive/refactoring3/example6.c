switch (mode) {
#ifndef NO_CREATE
	case 'c':
		create(filename, compress, argv);
		break;
#endif
	case 't':
		extract(filename, 0, flags);
		break;
	case 'x':
		extract(filename, 1, flags);
		break;
	}
