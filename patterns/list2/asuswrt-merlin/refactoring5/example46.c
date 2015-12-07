#ifdef INCLUDE_SHMEDIA
if (seen_stt_datalabel)
		{
		  struct elf_sh_link_hash_entry *eh
		    = (struct elf_sh_link_hash_entry *) h;

		  eh->datalabel_got.refcount += 1;
		}
	      else
#endif
		h->got.refcount += 1;
