switch (gc_option) {
#ifdef WITH_LIBGC
	case gc_opt_boehm: return GC_MALLOC(s0);
#endif
	case gc_opt_malloc: return calloc(1, s0);
	case gc_opt_large:
	default: return large_alloc(s0);
	}
