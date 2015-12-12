switch(knd) {
#     ifdef STUBBORN_ALLOC
	case STUBBORN:
	    return(GC_malloc_stubborn((size_t)lb));
#     endif
	case PTRFREE:
	    return(GC_malloc_atomic((size_t)lb));
	case NORMAL:
	    return(GC_malloc((size_t)lb));
	case UNCOLLECTABLE:
	    return(GC_malloc_uncollectable((size_t)lb));
#       ifdef ATOMIC_UNCOLLECTABLE
	  case AUNCOLLECTABLE:
	    return(GC_malloc_atomic_uncollectable((size_t)lb));
#	endif /* ATOMIC_UNCOLLECTABLE */
	default:
	    return(GC_generic_malloc(lb,knd));
    }
