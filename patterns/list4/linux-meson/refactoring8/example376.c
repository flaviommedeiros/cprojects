static void set_rule(uleb128_t reg, enum item_location where, uleb128_t value,
		     struct unwind_state *state)
{
	if (reg < ARRAY_SIZE(state->regs)) {
		state->regs[reg].where = where;
		state->regs[reg].value = value;

#ifdef UNWIND_DEBUG
		unw_debug("r%lu: ", reg);
		switch (where) {
		case Nowhere:
			unw_debug("s ");
			break;
		case Memory:
			unw_debug("c(%lu) ", value);
			break;
		case Register:
			unw_debug("r(%lu) ", value);
			break;
		case Value:
			unw_debug("v(%lu) ", value);
			break;
		default:
			break;
		}
#endif
	}
}
