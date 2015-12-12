switch(kind) {
	  case PTRFREE:
	    GC_err_puts("PTRFREE");
	    break;
	  case NORMAL:
	    GC_err_puts("NORMAL");
	    break;
	  case UNCOLLECTABLE:
	    GC_err_puts("UNCOLLECTABLE");
	    break;
#	  ifdef ATOMIC_UNCOLLECTABLE
	    case AUNCOLLECTABLE:
	      GC_err_puts("ATOMIC UNCOLLECTABLE");
	      break;
#	  endif
	  case STUBBORN:
	    GC_err_puts("STUBBORN");
	    break;
	  default:
	    GC_err_printf("kind %d, descr 0x%lx", kind,
			  (unsigned long)(hhdr -> hb_descr));
	}
