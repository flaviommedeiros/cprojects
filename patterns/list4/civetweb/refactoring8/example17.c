static const luaL_Reg dblib[] = {
    {"isopen",              db_isopen               },
    {"last_insert_rowid",   db_last_insert_rowid    },
    {"changes",             db_changes              },
    {"total_changes",       db_total_changes        },
    {"errcode",             db_errcode              },
    {"error_code",          db_errcode              },
    {"errmsg",              db_errmsg               },
    {"error_message",       db_errmsg               },
    {"interrupt",           db_interrupt            },

    {"create_function",     db_create_function      },
    {"create_aggregate",    db_create_aggregate     },
    {"create_collation",    db_create_collation     },
    {"load_extension",      db_load_extension       },

    {"trace",               db_trace                },
    {"progress_handler",    db_progress_handler     },
    {"busy_timeout",        db_busy_timeout         },
    {"busy_handler",        db_busy_handler         },
#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK
    {"update_hook",         db_update_hook          },
    {"commit_hook",         db_commit_hook          },
    {"rollback_hook",       db_rollback_hook        },
#endif

    {"prepare",             db_prepare              },
    {"rows",                db_rows                 },
    {"urows",               db_urows                },
    {"nrows",               db_nrows                },

    {"exec",                db_exec                 },
    {"execute",             db_exec                 },
    {"close",               db_close                },
    {"close_vm",            db_close_vm             },

    {"__tostring",          db_tostring             },
    {"__gc",                db_gc                   },

    {NULL, NULL}
};
