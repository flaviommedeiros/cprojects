switch (len) {
	case 2:
		*dest = byterev_2(x);
		break;
	case 4:
		*dest = byterev_4(x);
		break;
#ifdef __powerpc64__
	case 8:
		*dest = byterev_8(x);
		break;
#endif
	}
