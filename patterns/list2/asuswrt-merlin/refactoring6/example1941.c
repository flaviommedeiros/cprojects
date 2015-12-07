if (rel->r_type != R_SH_IMM32
#ifdef COFF_WITH_PE
	  && rel->r_type != R_SH_IMM32CE
	  && rel->r_type != R_SH_IMAGEBASE
#endif
	  && rel->r_type != R_SH_PCDISP)
	continue;
