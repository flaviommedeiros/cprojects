int expr_compare_type(enum expr_type t1, enum expr_type t2)
{
#if 0
	return 1;
#else
	if (t1 == t2)
		return 0;
	switch (t1) {
	case E_EQUAL:
	case E_UNEQUAL:
		if (t2 == E_NOT)
			return 1;
	case E_NOT:
		if (t2 == E_AND)
			return 1;
	case E_AND:
		if (t2 == E_OR)
			return 1;
	case E_OR:
		if (t2 == E_LIST)
			return 1;
	case E_LIST:
		if (t2 == 0)
			return 1;
	default:
		return -1;
	}
	printf("[%dgt%d?]", t1, t2);
	return 0;
#endif
}
