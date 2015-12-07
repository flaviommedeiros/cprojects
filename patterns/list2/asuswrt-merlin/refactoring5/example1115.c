#ifdef INCLUDE_SHMEDIA
if (rel->r_addend & 1)
		{
		  if (local_got_refcounts[symtab_hdr->sh_info + r_symndx] > 0)
		    local_got_refcounts[symtab_hdr->sh_info + r_symndx] -= 1;
		}
	      else
#endif
		if (local_got_refcounts[r_symndx] > 0)
		  local_got_refcounts[r_symndx] -= 1;
