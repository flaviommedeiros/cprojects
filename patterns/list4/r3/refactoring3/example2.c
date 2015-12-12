switch (action) {

	case A_AND: val1 &= val2; break;
	case A_OR:  val1 |= val2; break;
	case A_XOR:  val1 ^= val2; break;
	case A_COMPLEMENT: val1 = 1 & ~val1; break;

	case A_RANDOM:
		if (D_REF(2)) { // /seed
			// random/seed false restarts; true randomizes
			Set_Random(val1 ? (REBINT)OS_DELTA_TIME(0, 0) : 1);
			return R_UNSET;
		}
		DECIDE(Random_Int(D_REF(3)) & 1);  // /secure

	case A_MAKE:
	case A_TO:
		// As a "Rebol conversion", TO falls in line with the rest of the
		// interpreter canon that all non-none non-logic values are
		// considered effectively "truth".  As a construction routine,
		// MAKE takes more liberties in the meaning of its parameters,
		// so it lets zero values be false.
		if (IS_NONE(arg) ||
			(IS_LOGIC(arg) && !VAL_LOGIC(arg)) ||
			(IS_INTEGER(arg) && (action == A_MAKE && VAL_INT64(arg) == 0)) ||
			((IS_DECIMAL(arg) || IS_PERCENT(arg)) && (action == A_MAKE && VAL_DECIMAL(arg) == 0.0)) ||
			(IS_MONEY(arg) && (action == A_MAKE && deci_is_zero(VAL_DECI(arg))))
		) goto is_false;
		goto is_true;

#ifdef removed
	case A_CHANGE:
		if (IS_NONE(arg)) val1 = 0;
		else if (IS_INTEGER(arg)) val1 = Int32(arg);
		else if (IS_LOGIC(arg)) val1 = TRUE;
		else Trap_Arg(arg);
		break;
#endif

	default:
		Trap_Action(REB_LOGIC, action);
	}
