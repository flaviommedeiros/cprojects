#ifdef COMPILE_PCRE8
if (base_list[0] == OP_CLASS || (!utf && base_list[0] == OP_NCLASS))
#else
    if (base_list[0] == OP_CLASS)
#endif
      {
      set1 = (pcre_uint8 *)(base_end - base_list[2]);
      list_ptr = list;
      }
    else
      {
      set1 = (pcre_uint8 *)(code - list[2]);
      list_ptr = base_list;
      }
