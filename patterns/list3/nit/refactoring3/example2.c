switch (gc_option) {
#ifdef WITH_LIBGC
	case gc_opt_boehm: GC_gcollect(); break;
#endif
	default: break; /* nothing can be done */
	}
