switch (hhdr -> hb_obj_kind) {
#    ifdef STUBBORN_ALLOC
      case STUBBORN:
        result = GC_debug_malloc_stubborn(lb, OPT_RA s, i);
        break;
#    endif
      case NORMAL:
        result = GC_debug_malloc(lb, OPT_RA s, i);
        break;
      case PTRFREE:
        result = GC_debug_malloc_atomic(lb, OPT_RA s, i);
        break;
      case UNCOLLECTABLE:
	result = GC_debug_malloc_uncollectable(lb, OPT_RA s, i);
 	break;
#    ifdef ATOMIC_UNCOLLECTABLE
      case AUNCOLLECTABLE:
	result = GC_debug_malloc_atomic_uncollectable(lb, OPT_RA s, i);
	break;
#    endif
      default:
        GC_err_printf("GC_debug_realloc: encountered bad kind\n");
        ABORT("bad kind");
    }
