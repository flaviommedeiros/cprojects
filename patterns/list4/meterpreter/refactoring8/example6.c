static Elf32_Sym libdl_symtab[] = {
      // total length of libdl_info.strtab, including trailing 0
      // This is actually the the STH_UNDEF entry. Technically, it's
      // supposed to have st_name == 0, but instead, it points to an index
      // in the strtab with a \0 to make iterating through the symtab easier.
    { st_name: sizeof(ANDROID_LIBDL_STRTAB) - 1,
    },
    { st_name: 0,   // starting index of the name in libdl_info.strtab
      st_value: (Elf32_Addr) &dlopen,
      st_info: STB_GLOBAL << 4,
      st_shndx: 1,
    },
    { st_name: 7,
      st_value: (Elf32_Addr) &dlclose,
      st_info: STB_GLOBAL << 4,
      st_shndx: 1,
    },
    { st_name: 15,
      st_value: (Elf32_Addr) &dlsym,
      st_info: STB_GLOBAL << 4,
      st_shndx: 1,
    },
    { st_name: 21,
      st_value: (Elf32_Addr) &dlerror,
      st_info: STB_GLOBAL << 4,
      st_shndx: 1,
    },
    { st_name: 29,
      st_value: (Elf32_Addr) &dladdr,
      st_info: STB_GLOBAL << 4,
      st_shndx: 1,
    },
#ifdef ANDROID_ARM_LINKER
    { st_name: 36,
      st_value: (Elf32_Addr) &dl_unwind_find_exidx,
      st_info: STB_GLOBAL << 4,
      st_shndx: 1,
    },
#elif defined(ANDROID_X86_LINKER)
    { st_name: 36,
      st_value: (Elf32_Addr) &dl_iterate_phdr,
      st_info: STB_GLOBAL << 4,
      st_shndx: 1,
    },
    { st_name: 52,
      st_value: (Elf32_Addr) &dlopenbuf,
      st_info: STB_GLOBAL << 4,
      st_shndx: 1,
    }, // once arm is supported, move this before optional symbols 
#elif defined(ANDROID_SH_LINKER)
    { st_name: 36,
      st_value: (Elf32_Addr) &dl_iterate_phdr,
      st_info: STB_GLOBAL << 4,
      st_shndx: 1,
    },
#endif

};
