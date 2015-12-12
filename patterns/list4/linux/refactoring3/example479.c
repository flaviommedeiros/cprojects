switch (size) {
	case 2:
		*valp = byterev_2(*valp);
		break;
	case 4:
		*valp = byterev_4(*valp);
		break;
#ifdef __powerpc64__
	case 8:
		*valp = byterev_8(*valp);
		break;
#endif
	}
