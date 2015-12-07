#ifdef COFF_WITH_PE
if (irelscan->r_type != R_SH_IMM32
	      && irelscan->r_type != R_SH_IMAGEBASE
	      && irelscan->r_type != R_SH_IMM32CE)
#else
	  if (irelscan->r_type != R_SH_IMM32)
#endif
	    continue;
