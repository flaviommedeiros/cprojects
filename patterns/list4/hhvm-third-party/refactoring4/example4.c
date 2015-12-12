#if (defined SLJIT_VERBOSE && SLJIT_VERBOSE) || (defined SLJIT_DEBUG && SLJIT_DEBUG)
if (offset != 0)
		return sljit_emit_op2(compiler, SLJIT_ADD | SLJIT_KEEP_FLAGS, dst, dstw, SLJIT_SP, 0, SLJIT_IMM, offset);
