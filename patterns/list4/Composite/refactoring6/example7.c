if (r & ~(
		FE_TONEAREST
#ifdef FE_DOWNWARD
		|FE_DOWNWARD
#endif
#ifdef FE_UPWARD
		|FE_UPWARD
#endif
#ifdef FE_TOWARDZERO
		|FE_TOWARDZERO
#endif
		))
		return -1;
