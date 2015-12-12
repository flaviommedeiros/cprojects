if (!(sec->sh_flags & SHF_ALLOC)
#if 1 /* FIXME: ??? */
#ifndef CONFIG_KALLSYMS_ALL
	    || !(sec->sh_flags & SHF_EXECINSTR)
#endif
#endif
	    )
		return false;
