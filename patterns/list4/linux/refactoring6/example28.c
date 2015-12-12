if (!(elf64->e_ident[EI_MAG0]  == ELFMAG0	&&
	      elf64->e_ident[EI_MAG1]  == ELFMAG1	&&
	      elf64->e_ident[EI_MAG2]  == ELFMAG2	&&
	      elf64->e_ident[EI_MAG3]  == ELFMAG3	&&
	      elf64->e_ident[EI_CLASS] == ELFCLASS64	&&
#ifdef __LITTLE_ENDIAN__
	      elf64->e_ident[EI_DATA]  == ELFDATA2LSB	&&
#else
	      elf64->e_ident[EI_DATA]  == ELFDATA2MSB	&&
#endif
	      (elf64->e_type            == ET_EXEC ||
	       elf64->e_type            == ET_DYN)	&&
	      elf64->e_machine         == EM_PPC64))
		return 0;
