DUK_LOCAL const duk__two_arg_func duk__two_arg_funcs[] = {
#if defined(DUK_USE_AVOID_PLATFORM_FUNCPTRS)
	duk__atan2,
	duk__pow_fixed
#else
	DUK_ATAN2,
	duk__pow_fixed
#endif
};
