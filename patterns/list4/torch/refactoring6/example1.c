if (LJ_LIKELY(J->flags & JIT_F_OPT_LOOP) && ofs
#if LJ_TARGET_ARM
	  && (sz == 1 || sz == 4)
#endif
	  ) {
	ptr = emitir(IRT(IR_ADD, IRT_PTR), ptr, lj_ir_kintp(J, ofs));
	ofs = 0;
      }
