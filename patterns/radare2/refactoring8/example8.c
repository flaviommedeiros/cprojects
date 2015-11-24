ut64 get_import_addr(struct Elf_(r_bin_elf_obj_t) *bin, int sym) {
	Elf_(Rel) *rel = NULL;
	Elf_(Shdr) *rel_shdr;
	Elf_(Addr) plt_sym_addr;
	ut64 got_addr, got_offset;
	ut64 plt_addr, plt_offset;
	int j, k, tsize, len, nrel;

	if (!bin->shdr || !bin->strtab)
		return -1;
	if ((plt_offset = Elf_(r_bin_elf_get_section_offset) (bin, ".plt")) == -1)
		return -1;
	if ((plt_addr = Elf_(r_bin_elf_get_section_addr) (bin, ".plt")) == -1)
		return -1;

	if ((got_offset = Elf_(r_bin_elf_get_section_offset) (bin, ".got")) == -1 &&
		(got_offset = Elf_(r_bin_elf_get_section_offset) (bin, ".got.plt")) == -1)
		return -1;
	if ((got_addr = Elf_(r_bin_elf_get_section_addr) (bin, ".got")) == -1 &&
		(got_addr = Elf_(r_bin_elf_get_section_addr) (bin, ".got.plt")) == -1)
		return -1;

	if((rel_shdr = get_section_by_name(bin, ".rel.plt")) != NULL) {
		tsize = sizeof (Elf_(Rel));
	} else if((rel_shdr = get_section_by_name(bin, ".rela.plt")) != NULL) {
		tsize = sizeof (Elf_(Rela));
	} else {
		return -1;
	}

	nrel = (ut32)((int)rel_shdr->sh_size / (int)tsize);
	if (nrel < 1)
		return -1;
	int relsz = (int)nrel * sizeof (Elf_(Rel));
	if (relsz<1 || (rel = calloc (1, relsz)) == NULL) {
		perror ("malloc (rel)");
		return -1;
	}

	plt_sym_addr = -1;

	for (j = k = 0; j < rel_shdr->sh_size && k <nrel; j += tsize, k++) {
		if (rel_shdr->sh_offset+j > bin->size || rel_shdr->sh_offset+j+sizeof (Elf_(Rel)) > bin->size) {
			free (rel);
			return -1;
		}
		len = r_buf_fread_at (bin->b, rel_shdr->sh_offset + j,
			(ut8*)(&rel[k]),
#if R_BIN_ELF64
				      bin->endian?"2L":"2l",
#else
				      bin->endian?"2I":"2i",
#endif
				      1);
		if (len == -1) {
			eprintf ("Warning: read (rel)\n");
			break;
		}
		int reloc_type = ELF_R_TYPE (rel[k].r_info);
		int reloc_sym = ELF_R_SYM(rel[k].r_info);

		if (reloc_sym == sym) {
			int of = rel[k].r_offset;
			of = of - got_addr + got_offset;
			switch (bin->ehdr.e_machine) {
			case EM_SPARC:
			case EM_SPARCV9:
			case EM_SPARC32PLUS:
				if (reloc_type == 21) {
					plt_addr += k * 12 + 20;
					if (plt_addr & 1) {
						// thumb symbol
						plt_addr--;
					}
					free (rel);
					return plt_addr;
				} else {
					eprintf ("Unknown sparc reloc type %d\n", reloc_type);
				}
				/* SPARC */
				break;
			case EM_ARM:
			case EM_AARCH64:
				switch (reloc_type) {
				case 22:
					{
						plt_addr += k * 12 + 20;
						if (plt_addr & 1) {
							// thumb symbol
							plt_addr--;
						}
						free (rel);
						return plt_addr;
					}
					break;
				case 1026: // arm64 aarch64
					plt_sym_addr = plt_addr + k * 16 + 32;
					goto done;
				default:
					eprintf ("Unsupported relocation type for imports %d\n", reloc_type);
					break;
				}
				break;
			case EM_386:
			case EM_X86_64:
				switch (reloc_type) {
				case 7:
					if (of+sizeof(Elf_(Addr)) >= bin->b->length) {
						// do nothing
					} else {
						// ONLY FOR X86
						if (of > bin->size || of + sizeof (Elf_(Addr)) > bin->size) {
							free (rel);
							return -1;
						}
						if (r_buf_read_at (bin->b, of,
									(ut8*)&plt_sym_addr, sizeof (Elf_(Addr))) == -1) {
							eprintf ("Warning: read (got)\n");
							break;
						}
					}
					plt_sym_addr -= 6;
					goto done;
					break;
				default:
					eprintf ("Unsupported relocation type for imports %d\n", reloc_type);
					eprintf ("0x%"PFMT64x" - 0x%"PFMT64x" i \n", (ut64)rel[k].r_offset, (ut64)rel[k].r_info);
					free (rel);
					return of;
					break;
				}
				break;
			default:
				eprintf ("Unsupported relocs for this arch %d\n",
					bin->ehdr.e_machine);
				break;
			}
		}
	}
done:
	free (rel);
	return plt_sym_addr;
}
