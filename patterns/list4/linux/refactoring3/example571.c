switch (opcode & MASK_ROUNDING_PRECISION) {
	case ROUND_SINGLE:
		{
			fpa11->fType[getFn(opcode)] = typeSingle;
			fpa11->fpreg[getFn(opcode)].fSingle = int32_to_float32(&roundData, readRegister(getRd(opcode)));
		}
		break;

	case ROUND_DOUBLE:
		{
			fpa11->fType[getFn(opcode)] = typeDouble;
			fpa11->fpreg[getFn(opcode)].fDouble = int32_to_float64(readRegister(getRd(opcode)));
		}
		break;

#ifdef CONFIG_FPE_NWFPE_XP
	case ROUND_EXTENDED:
		{
			fpa11->fType[getFn(opcode)] = typeExtended;
			fpa11->fpreg[getFn(opcode)].fExtended = int32_to_floatx80(readRegister(getRd(opcode)));
		}
		break;
#endif

	default:
		return 0;
	}
