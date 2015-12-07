if (r_type != R_SH_IMM32
#ifdef COFF_WITH_PE
      && r_type != R_SH_IMM32CE
      && r_type != R_SH_IMAGEBASE
#endif
      && (r_type != R_SH_PCDISP
	  || (symbol_in->flags & BSF_LOCAL) != 0))
    return bfd_reloc_ok;
