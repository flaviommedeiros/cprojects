#if LJ_HASJIT
if ((flags & JIT_F_SSE2))
#endif
    J->flags = flags | JIT_F_ON | JIT_F_OPT_DEFAULT;
