static const luaL_Reg sqlitelib[] = {
    {"lversion",        lsqlite_lversion        },
    {"version",         lsqlite_version         },
    {"complete",        lsqlite_complete        },
#ifndef WIN32
    {"temp_directory",  lsqlite_temp_directory  },
#endif
    {"open",            lsqlite_open            },
    {"open_memory",     lsqlite_open_memory     },

    {"__newindex",      lsqlite_newindex        },
    {NULL, NULL}
};
