const m_option_t mp_opts[] = {
    // handled in command line pre-parser (parse_commandline.c)
    {"v", CONF_TYPE_STORE, CONF_GLOBAL | CONF_NOCFG, .offset = -1},
    {"playlist", CONF_TYPE_STRING, CONF_NOCFG | M_OPT_MIN | M_OPT_FIXED | M_OPT_FILE,
     .min = 1, .offset = -1},
    {"{", CONF_TYPE_STORE, CONF_NOCFG | M_OPT_FIXED, .offset = -1},
    {"}", CONF_TYPE_STORE, CONF_NOCFG | M_OPT_FIXED, .offset = -1},

    // handled in m_config.c
    { "include", CONF_TYPE_STRING, M_OPT_FIXED | M_OPT_FILE, .offset = -1},
    { "profile", CONF_TYPE_STRING_LIST, M_OPT_FIXED, .offset = -1},
    { "show-profile", CONF_TYPE_STRING, CONF_NOCFG | M_OPT_FIXED, .offset = -1},
    { "list-options", CONF_TYPE_STORE, CONF_NOCFG | M_OPT_FIXED, .offset = -1},

    OPT_FLAG("shuffle", shuffle, 0),

// ------------------------- common options --------------------
    OPT_FLAG("quiet", quiet, CONF_GLOBAL),
    OPT_FLAG_STORE("really-quiet", verbose, CONF_GLOBAL | CONF_PRE_PARSE, -10),
    OPT_FLAG("terminal", use_terminal, CONF_GLOBAL | CONF_PRE_PARSE | M_OPT_TERM),
    OPT_GENERAL(char**, "msg-level", msg_levels, CONF_GLOBAL|CONF_PRE_PARSE |
                M_OPT_TERM, .type = &m_option_type_msglevels),
    OPT_STRING("dump-stats", dump_stats, CONF_GLOBAL | CONF_PRE_PARSE),
    OPT_FLAG("msg-color", msg_color, CONF_GLOBAL | CONF_PRE_PARSE | M_OPT_TERM),
    OPT_STRING("log-file", log_file, CONF_GLOBAL | CONF_PRE_PARSE | M_OPT_FILE),
    OPT_FLAG("msg-module", msg_module, CONF_GLOBAL | M_OPT_TERM),
    OPT_FLAG("msg-time", msg_time, CONF_GLOBAL | M_OPT_TERM),
#ifdef _WIN32
    OPT_CHOICE("priority", w32_priority, 0,
               ({"no",          0},
                {"realtime",    REALTIME_PRIORITY_CLASS},
                {"high",        HIGH_PRIORITY_CLASS},
                {"abovenormal", ABOVE_NORMAL_PRIORITY_CLASS},
                {"normal",      NORMAL_PRIORITY_CLASS},
                {"belownormal", BELOW_NORMAL_PRIORITY_CLASS},
                {"idle",        IDLE_PRIORITY_CLASS})),
#endif
    OPT_FLAG("config", load_config, CONF_GLOBAL | CONF_PRE_PARSE),
    OPT_STRING("config-dir", force_configdir,
               CONF_GLOBAL | CONF_NOCFG | CONF_PRE_PARSE),
    OPT_STRINGLIST("reset-on-next-file", reset_options, M_OPT_GLOBAL),

#if HAVE_LUA
    OPT_STRINGLIST("script", script_files, CONF_GLOBAL | M_OPT_FILE),
    OPT_KEYVALUELIST("script-opts", script_opts, M_OPT_GLOBAL),
    OPT_FLAG("osc", lua_load_osc, CONF_GLOBAL),
    OPT_FLAG("ytdl", lua_load_ytdl, CONF_GLOBAL),
    OPT_STRING("ytdl-format", lua_ytdl_format, CONF_GLOBAL),
    OPT_KEYVALUELIST("ytdl-raw-options", lua_ytdl_raw_options, CONF_GLOBAL),
    OPT_FLAG("load-scripts", auto_load_scripts, CONF_GLOBAL),
#endif

// ------------------------- stream options --------------------

    OPT_CHOICE_OR_INT("cache", stream_cache.size, 0, 32, 0x7fffffff,
                      ({"no", 0},
                       {"auto", -1}
