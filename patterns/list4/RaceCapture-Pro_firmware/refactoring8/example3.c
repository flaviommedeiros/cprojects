static const luaL_Reg lualibs[] = {
    {"", luaopen_base},
    {LUA_LOADLIBNAME, luaopen_package},
    {LUA_STRLIBNAME, luaopen_string},
#if LUA_OPTIMIZE_MEMORY == 0
    {LUA_MATHLIBNAME, luaopen_math},
    {LUA_OSLIBNAME, luaopen_os},
    {LUA_TABLIBNAME, luaopen_table},
    {LUA_DBLIBNAME, luaopen_debug},
#endif
    {NULL, NULL}
};
