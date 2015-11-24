static RBinReloc *reloc_convert(struct Elf_(r_bin_elf_obj_t) *bin, RBinElfReloc *rel, ut64 GOT) {
	RBinReloc *r = NULL;
	ut64 B, P;

	if (!bin || !rel) return NULL;
	B = bin->baddr;
	P = B + rel->rva;
	if (!(r = R_NEW0 (RBinReloc)))
		return r;

	r->import = NULL;
	r->symbol = NULL;
	r->addend = rel->addend;
	if (rel->sym) {
		if (rel->sym < bin->imports_by_ord_size && bin->imports_by_ord[rel->sym])
			r->import = bin->imports_by_ord[rel->sym];
		else if (rel->sym < bin->symbols_by_ord_size && bin->symbols_by_ord[rel->sym])
			r->symbol = bin->symbols_by_ord[rel->sym];
	}
	r->vaddr = rel->rva;
	r->paddr = rel->offset;
	// if object file
	if (bin->ehdr.e_type == ET_REL) {
		ut64 text;
		if ((text = Elf_ (r_bin_elf_get_section_offset) (bin, ".text")) != -1) {
			r->vaddr += text;
		}
	}

	#define SET(T) r->type = R_BIN_RELOC_ ## T; r->additive = 0; return r
	#define ADD(T, A) r->type = R_BIN_RELOC_ ## T; r->addend += A; r->additive = !rel->is_rela; return r

	switch (bin->ehdr.e_machine) {
	case EM_386: switch (rel->type) {
		case R_386_NONE:     break; // malloc then free. meh. then again, there's no real world use for _NONE.
		case R_386_32:       ADD(32, 0);
		case R_386_PC32:     ADD(32,-P);
		case R_386_GLOB_DAT: SET(32);
		case R_386_JMP_SLOT: SET(32);
		case R_386_RELATIVE: ADD(32, B);
		case R_386_GOTOFF:   ADD(32,-GOT);
		case R_386_GOTPC:    ADD(32, GOT-P);
		case R_386_16:       ADD(16, 0);
		case R_386_PC16:     ADD(16,-P);
		case R_386_8:        ADD(8,  0);
		case R_386_PC8:      ADD(8, -P);
		case R_386_COPY:     ADD(64, 0); // XXX: copy symbol at runtime
		default: break; //eprintf("TODO(eddyb): uninmplemented ELF/x86 reloc type %i\n", rel->type);
		}
		break;
	case EM_X86_64: switch (rel->type) {
		case R_X86_64_NONE:	break; // malloc then free. meh. then again, there's no real world use for _NONE.
		case R_X86_64_64:	ADD(64, 0);
		case R_X86_64_PLT32:	ADD(32,-P /* +L */);
		case R_X86_64_GOT32:	ADD(32, GOT);
		case R_X86_64_PC32:	ADD(32,-P);
		case R_X86_64_GLOB_DAT: r->vaddr -= rel->sto; SET(64);
		case R_X86_64_JUMP_SLOT: r->vaddr -= rel->sto; SET(64);
		case R_X86_64_RELATIVE:	ADD(64, B);
		case R_X86_64_32:	ADD(32, 0);
		case R_X86_64_32S:	ADD(32, 0);
		case R_X86_64_16:	ADD(16, 0);
		case R_X86_64_PC16:	ADD(16,-P);
		case R_X86_64_8:	ADD(8,  0);
		case R_X86_64_PC8:	ADD(8, -P);
		case R_X86_64_GOTPCREL:	ADD(64, GOT-P);
		case R_X86_64_COPY:	ADD(64, 0); // XXX: copy symbol at runtime
		default: break; ////eprintf("TODO(eddyb): uninmplemented ELF/x64 reloc type %i\n", rel->type);
		}
		break;
	case EM_ARM: switch (rel->type) {
		case R_ARM_NONE:	break; // malloc then free. meh. then again, there's no real world use for _NONE.
		case R_ARM_ABS32:	ADD(32, 0);
		case R_ARM_REL32:	ADD(32,-P);
		case R_ARM_ABS16:	ADD(16, 0);
		case R_ARM_ABS8:	ADD(8,  0);
		case R_ARM_SBREL32:	ADD(32, -B);
		case R_ARM_GLOB_DAT:	ADD(32, 0);
		case R_ARM_JUMP_SLOT:	ADD(32, 0);
		case R_ARM_RELATIVE:	ADD(32, B);
		case R_ARM_GOTOFF:	ADD(32,-GOT);
		default: ADD(32,GOT); break; // reg relocations
		 ////eprintf("TODO(eddyb): uninmplemented ELF/ARM reloc type %i\n", rel->type);
		}
		break;
	default: break;
#if 0
		if (!(str = Elf_(r_bin_elf_get_machine_name) (bin)))
			break;
		eprintf("TODO(eddyb): uninmplemented ELF reloc_convert for %s\n", str);
		free(str);
#endif
	}

	#undef SET
	#undef ADD

	free(r);
	return 0;
}
