switch( argv[1][0] ) {
	case 'c': certify(); break;
	case 'e': encrypt(argv[2], argv[3]); break;
	case 'd': decrypt(argv[2], argv[3]); break;
	case 't': prt_tables(); break;
#ifndef unix
	case 'b': bernstein(argv[2]);	break;
#endif
	}
