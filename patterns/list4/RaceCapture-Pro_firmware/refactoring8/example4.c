const luaR_table lua_rotable[] = {
#if LUA_OPTIMIZE_MEMORY > 0
    {LUA_MATHLIBNAME, mathlib, mathlib_vals},
    {LUA_OSLIBNAME, syslib, NULL},
    {LUA_TABLIBNAME, tab_funcs, NULL},
    {LUA_DBLIBNAME, dblib, NULL},
    {LUA_COLIBNAME, co_funcs, NULL},
#endif
    {NULL, NULL, NULL}
};
