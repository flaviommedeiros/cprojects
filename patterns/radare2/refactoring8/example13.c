static int bin_pe_parse_imports(struct PE_(r_bin_pe_obj_t)* bin,
				struct r_bin_pe_import_t** importp, int* nimp,
				const char* dll_name,
				PE_DWord OriginalFirstThunk,
				PE_DWord FirstThunk) {

	char import_name[PE_NAME_LENGTH + 1];
	char name[PE_NAME_LENGTH + 1];
	PE_Word import_hint, import_ordinal = 0;
	PE_DWord import_table = 0, off = 0;
	int i = 0, len;
	Sdb *db = NULL;
	char *sdb_module = NULL;
	char *symname;
	char *filename;
	char *symdllname = NULL;

	if (!dll_name || *dll_name == '0')
		return 0;

	if ((off = bin_pe_vaddr_to_paddr(bin, OriginalFirstThunk)) == 0 &&
		(off = bin_pe_vaddr_to_paddr(bin, FirstThunk)) == 0)
		return 0;

	do {
		if (import_ordinal >= UT16_MAX) break;
		if (off + i * sizeof(PE_DWord) > bin->size) break;
		len = r_buf_read_at (bin->b, off + i * sizeof (PE_DWord),
				(ut8*)&import_table, sizeof (PE_DWord));
		if (len == -1 || len == 0) {
			eprintf("Warning: read (import table)\n");
			goto error;
		}
		else if (import_table) {
			if (import_table & ILT_MASK1) {
				import_ordinal = import_table & ILT_MASK2;
				import_hint = 0;
				snprintf (import_name, PE_NAME_LENGTH, "%s_Ordinal_%i",
					dll_name, import_ordinal);
				free (symdllname);
				strncpy (name, dll_name, sizeof (name)-1);
				name[sizeof(name)-1] = 0;
				symdllname = strdup (name);

				// remove the trailling ".dll"
				size_t len = strlen (symdllname);
				len = len < 4 ? 0 : len - 4;
				symdllname[len] = 0;

				if (!sdb_module || strcmp (symdllname, sdb_module)) {
					sdb_free (db);
					db = NULL;
					free (sdb_module);
					sdb_module = strdup (symdllname);
					filename = sdb_fmt (1, "%s.sdb", symdllname);
					if (r_file_exists (filename)) {
						db = sdb_new (NULL, filename, 0);
					} else {
#if __WINDOWS__
						filename = sdb_fmt (1, "share/radare2/"R2_VERSION"/format/dll/%s.sdb", symdllname);
#else
						filename = sdb_fmt (1, R2_PREFIX"/share/radare2/" R2_VERSION"/format/dll/%s.sdb", symdllname);
#endif
						if (r_file_exists (filename)) {
							db = sdb_new (NULL, filename, 0);
						}
					}
				}
				if (db) {
					// ordinal-1 because we enumerate starting at 0
					symname = resolveModuleOrdinal (db, symdllname, import_ordinal-1);
					if (symname) {
						snprintf (import_name,
							PE_NAME_LENGTH,
							"%s_%s", dll_name, symname);
					}
				} else  {
					eprintf ("Cannot find %s\n", filename);

				}
			} else {
				import_ordinal++;
				const ut64 off = bin_pe_vaddr_to_paddr(bin, import_table);
				if (off > bin->size || (off + sizeof (PE_Word)) > bin->size) {
					eprintf ("Warning: off > bin->size\n");
					goto error;
				}
				len = r_buf_read_at (bin->b, off, (ut8*)&import_hint, sizeof (PE_Word));
				if (len < 1) {
					eprintf ("Warning: read import hint at 0x%08"PFMT64x"\n", off);
					goto error;
				}
				name[0] = '\0';
				len = r_buf_read_at (bin->b, off + sizeof(PE_Word),
							(ut8*)name, PE_NAME_LENGTH);
				if (len < 1) {
					eprintf ("Warning: read (import name)\n");
					goto error;
				} else if (!*name) {
					break;
				}
				name[PE_NAME_LENGTH] = '\0';
				snprintf (import_name, PE_NAME_LENGTH, "%s_%s", dll_name, name);
			}
			if (!(*importp = realloc (*importp, (*nimp + 1) * sizeof(struct r_bin_pe_import_t)))) {
				r_sys_perror ("realloc (import)");
				goto error;
			}
			memcpy((*importp)[*nimp].name, import_name, PE_NAME_LENGTH);
			(*importp)[*nimp].name[PE_NAME_LENGTH] = '\0';
			(*importp)[*nimp].vaddr = FirstThunk + i * sizeof (PE_DWord) \
				+ bin->nt_headers->optional_header.ImageBase;
			(*importp)[*nimp].paddr = bin_pe_vaddr_to_paddr(bin, FirstThunk) + i * sizeof(PE_DWord);
			(*importp)[*nimp].hint = import_hint;
			(*importp)[*nimp].ordinal = import_ordinal;
			(*importp)[*nimp].last = 0;
			(*nimp)++;
			i++;
		}
	} while (import_table);

	free (symdllname);
	free (sdb_module);
	return i;

error:
	free (symdllname);
	free (sdb_module);
	return false;
}
