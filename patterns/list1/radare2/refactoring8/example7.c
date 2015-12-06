static int init_dynamic_section (struct Elf_(r_bin_elf_obj_t) *bin) {
	Elf_(Dyn) *dyn = NULL;
	Elf_(Addr) strtabaddr = 0;
	char *strtab = NULL;
	size_t strsize = 0;
	int entries;
	int i, r;
	ut32 dyn_size;

	if (!bin || !bin->phdr || bin->ehdr.e_phnum == 0)
		return false;

	for (i = 0; i < bin->ehdr.e_phnum ; i++) {
		if (bin->phdr[i].p_type == PT_DYNAMIC) break;
	}
	if (i == bin->ehdr.e_phnum) {
		// we didn't find the PT_DYNAMIC section
		return false;
	}
	if (bin->phdr[i].p_filesz > bin->size) {
		return false;
	}
	if (bin->phdr[i].p_offset > bin->size)
		return false;

	entries = (int)(bin->phdr[i].p_filesz / sizeof (Elf_(Dyn)));
	if (entries < 1)
		return false;
	dyn = (Elf_(Dyn)*)calloc (entries, sizeof (Elf_(Dyn)));
	if (!dyn) return false;

	if (!UT32_MUL (&dyn_size, entries, sizeof (Elf_(Dyn)))) {
		free (dyn);
		return false;
	}
	if (!dyn_size) {
		free (dyn);
		return false;
	}
	if (bin->phdr[i].p_offset + dyn_size > bin->size) {
		free (dyn);
		return false;
	}

	r = r_buf_fread_at (bin->b, bin->phdr[i].p_offset, (ut8 *)dyn,
#if R_BIN_ELF64
		bin->endian ? "2L":"2l",
#else
		bin->endian ? "2I":"2i",
#endif
		entries);

	if (r == -1 || r == 0) {
		free (dyn);
		return false;
	}
	for (i = 0; i < entries; i++) {
		switch (dyn[i].d_tag) {
		case DT_STRTAB: strtabaddr = Elf_(r_bin_elf_v2p) (bin, dyn[i].d_un.d_ptr); break;
		case DT_STRSZ: strsize = dyn[i].d_un.d_val; break;
		default: break;
		}
	}
	if (!strtabaddr || strtabaddr > bin->size ||
	strsize > ST32_MAX || strsize == 0 || strsize > bin->size) {
		free (dyn);
		return false;
	}
	strtab = (char *)calloc (1, strsize+1);
	if (!strtab) {
		free (dyn);
		return false;
	}
	if (strtabaddr + strsize > bin->size) {
		free (dyn);
		free (strtab);
		return false;
	}
	r = r_buf_read_at (bin->b, strtabaddr, (ut8 *)strtab, strsize);
	if (r == 0 || r == -1) {
		free (dyn);
		free (strtab);
		return false;
	}
	bin->dyn_buf = dyn;
	bin->dyn_entries = entries;
	bin->strtab = strtab;
	bin->strtab_size = strsize;
	r = Elf_(r_bin_elf_has_relro)(bin);
	if (r == 2) sdb_set (bin->kv, "elf.relro", "full relro", 0);
	else if (r == 1) sdb_set (bin->kv, "elf.relro", "partial relro", 0);
	else sdb_set (bin->kv, "elf.relro", "no relro", 0);
	sdb_num_set (bin->kv, "elf_strtab.offset", strtabaddr, 0);
	sdb_num_set (bin->kv, "elf_strtab.size", strsize, 0);
	return true;
}
