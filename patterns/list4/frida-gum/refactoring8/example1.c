const gchar * primitive_type_name[] = {
      "S8",
      "U8",
      "S16",
      "U16",
      "S32",
      "U32",
      "Float",
      "Double",
#if GLIB_SIZEOF_VOID_P == 8
      "S64",
      "U64"
#endif
  };
