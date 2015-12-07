if (irelfn->r_vaddr == paddr
#ifdef COFF_WITH_PE
	    && (irelfn->r_type == R_SH_IMM32
		|| irelfn->r_type == R_SH_IMM32CE
		|| irelfn->r_type == R_SH_IMAGEBASE)

#else
	    && irelfn->r_type == R_SH_IMM32
#endif
	    )
	  break;
