switch (nb) {
	case 2:
		val = byterev_2(val);
		break;
	case 4:
		val = byterev_4(val);
		break;
#ifdef __powerpc64__
	case 8:
		val = byterev_8(val);
		break;
#endif
	}
