#ifdef INCLUDE_SHMEDIA
if (rel->r_addend)
		    local_got_offsets[symtab_hdr->sh_info + r_symndx] |= 1;
		  else
#endif
		    local_got_offsets[r_symndx] |= 1;
