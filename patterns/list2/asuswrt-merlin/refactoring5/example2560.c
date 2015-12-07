#ifdef BFD64
if (ptr_size == 8)
			    r_symndx = ELF64_R_SYM (cookie->rel->r_info);
			  else
#endif
			    r_symndx = ELF32_R_SYM (cookie->rel->r_info);
