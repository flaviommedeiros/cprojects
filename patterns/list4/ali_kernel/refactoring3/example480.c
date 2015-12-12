switch (fpa11->fType[Fn]) {
	case typeSingle:
		val.f = float32_to_float64(fpa11->fpreg[Fn].fSingle);
		break;

#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		val.f = floatx80_to_float64(roundData, fpa11->fpreg[Fn].fExtended);
		break;
#endif

	default:
		val.f = fpa11->fpreg[Fn].fDouble;
	}
