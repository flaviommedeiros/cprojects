char* Elf_(r_bin_elf_get_osabi_name)(struct Elf_(r_bin_elf_obj_t) *bin) {
	/* Hack to identify OS */
	if (needle (bin, "openbsd")) return strdup ("openbsd");
	if (needle (bin, "netbsd")) return strdup ("netbsd");
	if (needle (bin, "freebsd")) return strdup ("freebsd");
	if (noodle (bin, "BEOS:APP_VERSION")) return strdup ("beos");
	if (needle (bin, "GNU")) return strdup ("linux");
	return strdup ("linux");
#if 0
	// XXX: this is wrong. openbsd bins are identified as linux ones.
	switch (bin->ehdr.e_ident[EI_OSABI]) {
	case ELFOSABI_ARM_AEABI:
	case ELFOSABI_ARM:        return strdup ("arm");
	case ELFOSABI_NONE:       return strdup ("linux"); // sysv
	case ELFOSABI_HPUX:       return strdup ("hpux");
	case ELFOSABI_NETBSD:     return strdup ("netbsd");
	case ELFOSABI_LINUX:      return strdup ("linux");
	case ELFOSABI_SOLARIS:    return strdup ("solaris");
	case ELFOSABI_AIX:        return strdup ("aix");
	case ELFOSABI_IRIX:       return strdup ("irix");
	case ELFOSABI_FREEBSD:    return strdup ("freebsd");
	case ELFOSABI_TRU64:      return strdup ("tru64");
	case ELFOSABI_MODESTO:    return strdup ("modesto");
	case ELFOSABI_OPENBSD:    return strdup ("openbsd");
	case ELFOSABI_STANDALONE: return strdup ("standalone");
	default:                  return r_str_newf ("<unknown: %x>", bin->ehdr.e_ident[EI_OSABI]);
	}
#endif
}
