switch(gc_option) {
#ifdef WITH_LIBGC
		case boehm: GC_INIT(); break;
#endif
		case nitgc: Nit_gc_init(); break;
		default: break; /* Nothing */
	}
