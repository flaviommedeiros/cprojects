cpu_type_t pref_cpu_types[2] = {
#if defined(__x86_64__)
    CPU_TYPE_X86,
#elif defined(__i386__)
    CPU_TYPE_X86_64,
#endif
    CPU_TYPE_ANY
  };
