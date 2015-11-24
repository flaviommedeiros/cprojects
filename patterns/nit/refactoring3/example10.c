switch(gc_option) {
#ifdef WITH_LIBGC
		case gc_opt_boehm: GC_INIT(); break;
#endif
		default: break; /* Nothing */
	}
