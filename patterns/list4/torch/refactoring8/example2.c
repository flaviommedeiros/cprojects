static const struct luaL_Reg torch_Storage_(_) [] = {
  {"size", torch_Storage_(__len__)},
  {"__len__", torch_Storage_(__len__)},
  {"__newindex__", torch_Storage_(__newindex__)},
  {"__index__", torch_Storage_(__index__)},
  {"resize", torch_Storage_(resize)},
  {"fill", torch_Storage_(fill)},
  {"copy", torch_Storage_(copy)},
  {"totable", torch_Storage_(totable)},
  {"write", torch_Storage_(write)},
  {"read", torch_Storage_(read)},
#if defined(TH_REAL_IS_CHAR) || defined(TH_REAL_IS_BYTE)
  {"string", torch_Storage_(string)},
#endif
  {NULL, NULL}
};
