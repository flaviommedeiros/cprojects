#ifdef INCLUDE_SHMEDIA
if (seen_stt_datalabel)
			{
			  struct elf_sh_link_hash_entry *hsh;

			  hsh = (struct elf_sh_link_hash_entry *)h;
			  hsh->datalabel_got.offset |= 1;
			}
		      else
#endif
			h->got.offset |= 1;
