if ((ct->info & CTF_VARARG)
#if LJ_TARGET_X86
	|| ctype_cconv(ct->info) != CTCC_CDECL
#endif
	)
      func = emitir(IRT(IR_CARG, IRT_NIL), func,
		    lj_ir_kint(J, ctype_typeid(cts, ct)));
