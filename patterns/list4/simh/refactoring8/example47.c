static SHTAB show_glob_tab[] = {
    { "CONFIGURATION",  &show_config,               0, HLP_SHOW_CONFIG },
    { "DEVICES",        &show_config,               1, HLP_SHOW_DEVICES },
    { "FEATURES",       &show_config,               2, HLP_SHOW_FEATURES },
    { "QUEUE",          &show_queue,                0, HLP_SHOW_QUEUE },
    { "TIME",           &show_time,                 0, HLP_SHOW_TIME },
    { "MODIFIERS",      &show_mod_names,            0, HLP_SHOW_MODIFIERS },
    { "NAMES",          &show_log_names,            0, HLP_SHOW_NAMES },
    { "SHOW",           &show_show_commands,        0, HLP_SHOW_SHOW },
    { "VERSION",        &show_version,              1, HLP_SHOW_VERSION },
    { "DEFAULT",        &show_default,              0, HLP_SHOW_DEFAULT },
    { "CONSOLE",        &sim_show_console,          0, HLP_SHOW_CONSOLE },
    { "REMOTE",         &sim_show_remote_console,   0, HLP_SHOW_REMOTE },
    { "BREAK",          &show_break,                0, HLP_SHOW_BREAK },
    { "LOG",            &sim_show_log,              0, HLP_SHOW_LOG },
    { "TELNET",         &sim_show_telnet,           0 },    /* deprecated */
    { "DEBUG",          &sim_show_debug,            0, HLP_SHOW_DEBUG },
    { "THROTTLE",       &sim_show_throt,            0, HLP_SHOW_THROTTLE },
    { "ASYNCH",         &sim_show_asynch,           0, HLP_SHOW_ASYNCH },
    { "ETHERNET",       &eth_show_devices,          0, HLP_SHOW_ETHERNET },
    { "SERIAL",         &sim_show_serial,           0, HLP_SHOW_SERIAL },
    { "MULTIPLEXER",    &tmxr_show_open_devices,    0, HLP_SHOW_MULTIPLEXER },
    { "MUX",            &tmxr_show_open_devices,    0, HLP_SHOW_MULTIPLEXER },
#if defined(USE_SIM_VIDEO)
    { "VIDEO",          &vid_show,                  0, HLP_SHOW_VIDEO },
#endif
    { "CLOCKS",         &sim_show_timers,           0, HLP_SHOW_CLOCKS },
    { "SEND",           &sim_show_send,             0, HLP_SHOW_SEND },
    { "EXPECT",         &sim_show_expect,           0, HLP_SHOW_EXPECT },
    { "ON",             &show_on,                   0, HLP_SHOW_ON },
    { NULL,             NULL,                       0 }
    };
