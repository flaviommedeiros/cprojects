switch (gc_option) {
#ifdef WITH_LIBGC
	case boehm: return GC_MALLOC(s0);
#endif
	case nitgc: return Nit_gc_malloc(s0);
	case gc_opt_malloc: return calloc(1, s0);
	case large:
	default: return large_alloc(s0);
	}
