switch (fpa11->fType[Fn]) {
	case typeSingle:
		{
			writeRegister(getRd(opcode), float32_to_int32(&roundData, fpa11->fpreg[Fn].fSingle));
		}
		break;

	case typeDouble:
		{
			writeRegister(getRd(opcode), float64_to_int32(&roundData, fpa11->fpreg[Fn].fDouble));
		}
		break;

#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		{
			writeRegister(getRd(opcode), floatx80_to_int32(&roundData, fpa11->fpreg[Fn].fExtended));
		}
		break;
#endif

	default:
		return 0;
	}
