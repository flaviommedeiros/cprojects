static luaL_Reg luax_exts[] = {
    {"cjson", luaopen_cjson_safe},
    {"zlib", luaopen_zlib},
    {"pack", luaopen_pack},
    {"socket.core", luaopen_socket_core},
    {"mime.core", luaopen_mime_core},
    {"lfs", luaopen_lfs},

#if CC_SQLITE_ENABLED > 0
    {"lsqlite3", luaopen_lsqlite3},
#endif

    {NULL, NULL}
};
