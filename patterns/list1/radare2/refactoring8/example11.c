static struct r_bin_elf_symbol_t* get_symbols_from_phdr (struct Elf_(r_bin_elf_obj_t) *bin, int type) {
	Elf_(Sym) *sym = NULL;
	Elf_(Addr) addr_sym_table = 0;
	struct r_bin_elf_symbol_t *ret = NULL;
	int j, k, r, tsize, nsym, ret_ctr;
	ut64 toffset;
	ut32 size;

	if (!bin || !bin->phdr || bin->ehdr.e_phnum == 0)
		return NULL;

	for (j = 0; j < bin->dyn_entries; j++) {
		if (bin->dyn_buf[j].d_tag == DT_SYMTAB) {
			addr_sym_table = Elf_(r_bin_elf_v2p) (bin, bin->dyn_buf[j].d_un.d_ptr);
			break;
		}
	}
	if (addr_sym_table) {
		//since ELF doesn't specify the symbol table size we are going to read until the end of the buffer
		// this might be overkill.
		nsym = (int)(bin->b->length - addr_sym_table) / sizeof (Elf_(Sym));
		if (nsym < 1)
			return NULL;
		sym = (Elf_(Sym)*) calloc (nsym, sizeof (Elf_(Sym)));
		if (!sym) {
			return NULL;
		}
		if (!UT32_MUL (&size, nsym, sizeof (Elf_(Sym)))) {
			free (sym);
			return NULL;
		}
		if (size < 1) {
			free (sym);
			return NULL;
		}
		if (addr_sym_table > bin->size || addr_sym_table+size > bin->size) {
			free (sym);
			return NULL;
		}
		r = r_buf_fread_at (bin->b, addr_sym_table , (ut8*)sym,
#if R_BIN_ELF64
					bin->endian? "I2cS2L": "i2cs2l",
#else
					bin->endian? "3I2cS": "3i2cs",
#endif
					nsym);
		if (r == 0 || r == -1) {
			free (sym);
			return NULL;
		}
		for (k = ret_ctr = 0 ; k < nsym ; k++) {
			if (k == 0)
				continue;
			if (type == R_BIN_ELF_IMPORTS && sym[k].st_shndx == STN_UNDEF) {
				if (sym[k].st_value)
					toffset = sym[k].st_value;
				else if ((toffset = get_import_addr (bin, k)) == -1)
					toffset = 0;
				tsize = 16;
			} else if (type == R_BIN_ELF_SYMBOLS && sym[k].st_shndx != STN_UNDEF &&
			  ELF_ST_TYPE(sym[k].st_info) != STT_SECTION && ELF_ST_TYPE(sym[k].st_info) != STT_FILE) {
				tsize = sym[k].st_size;
				toffset = (ut64)sym[k].st_value;
			} else continue;
			if ((ret = realloc (ret, (ret_ctr + 1) * sizeof (struct r_bin_elf_symbol_t))) == NULL) {
				free (sym);
				return NULL;
			}

			if (sym[k].st_name+2 > bin->strtab_size)
				// Since we are reading beyond the symbol table what's happening
				// is that some entry is trying to dereference the strtab beyond its capacity
				// is not a symbol so is the end
				goto done;

			ret[ret_ctr].offset = Elf_(r_bin_elf_v2p) (bin, toffset);
			ret[ret_ctr].size = tsize;
			{
			   int rest = R_MIN (ELF_STRING_LENGTH,128)-1;
			   int st_name = sym[k].st_name;
			   int maxsize = R_MIN (bin->size, bin->strtab_size);
			   if (st_name < 0 || st_name >= maxsize) {
					ret[ret_ctr].name[0] = 0;
			   } else {
					const int len = __strnlen (bin->strtab+st_name, rest);
					memcpy (ret[ret_ctr].name, &bin->strtab[st_name], len);
			   }
			}
			ret[ret_ctr].ordinal = k;
			ret[ret_ctr].name[ELF_STRING_LENGTH-2] = '\0';
			fill_symbol_bind_and_type (&ret[ret_ctr], &sym[k]);
			ret[ret_ctr].last = 0;
			ret_ctr++;
		}
done:
		{
			struct r_bin_elf_symbol_t *p =
				(struct r_bin_elf_symbol_t*)realloc (ret,
				(ret_ctr+1) * sizeof (struct r_bin_elf_symbol_t));
			if (!p) {
				free (ret);
				free (sym);
				return NULL;
			}
			ret = p;
		}
		ret[ret_ctr].last = 1;
		if (type == R_BIN_ELF_IMPORTS && !bin->imports_by_ord_size) {
			bin->imports_by_ord_size = ret_ctr;
			if (ret_ctr > 0)
				bin->imports_by_ord = (RBinImport**)calloc (ret_ctr, sizeof (RBinImport*));
			else
				bin->imports_by_ord = NULL;
		} else if (type == R_BIN_ELF_SYMBOLS && !bin->symbols_by_ord_size && ret_ctr) {
			bin->symbols_by_ord_size = ret_ctr;
			if (ret_ctr > 0)
				bin->symbols_by_ord = (RBinSymbol**)calloc (ret_ctr, sizeof (RBinSymbol*));
			else
				bin->imports_by_ord = NULL;
		}
	}
	//free (sym);
	return ret;
}
