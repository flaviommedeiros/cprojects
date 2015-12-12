const struct arch_desc arch_descs[] =
  {
#ifdef ISA_XMEGA
    { 
      .name = "avrxmega6",
      .pc_3bytes = 1,
      .has_eind = 1
    },
#else
    { 
      .name = "avr51",
      .pc_3bytes = 0,
      .has_eind = 0
    },
    {
      .name = "avr6",
      .pc_3bytes = 1,
      .has_eind = 1
    },
#endif
    { NULL, 0, 0}
  };
