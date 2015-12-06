switch (gc_option) {
	case gc_opt_malloc: return malloc(s0);
#ifdef WITH_LIBGC
	case gc_opt_boehm: return GC_MALLOC_ATOMIC(s0);
#endif

	default: return nit_alloc(s0);
	}
