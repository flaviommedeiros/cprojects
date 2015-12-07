#ifdef INCLUDE_SHMEDIA
if (seen_stt_datalabel)
		{
		  struct elf_sh_link_hash_entry *eh;
		  eh = (struct elf_sh_link_hash_entry *) h;
		  if (eh->datalabel_got.refcount > 0)
		    eh->datalabel_got.refcount -= 1;
		}
	      else
#endif
		if (h->got.refcount > 0)
		  h->got.refcount -= 1;
