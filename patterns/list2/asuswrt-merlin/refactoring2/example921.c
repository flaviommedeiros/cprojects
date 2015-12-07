#if SHT_RELM == SHT_RELA
if (!extsym || !extsym->st_name
			 || ELF_ST_BIND(extsym->st_info) != STB_LOCAL)
#endif
				value += rel->r_addend;
