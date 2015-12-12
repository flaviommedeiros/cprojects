switch (fpa11->fType[Fn]) {
	case typeDouble:
		val.f = float64_to_float32(roundData, fpa11->fpreg[Fn].fDouble);
		break;

#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		val.f = floatx80_to_float32(roundData, fpa11->fpreg[Fn].fExtended);
		break;
#endif

	default:
		val.f = fpa11->fpreg[Fn].fSingle;
	}
