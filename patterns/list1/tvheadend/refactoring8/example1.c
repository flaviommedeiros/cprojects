static api_hook_t ah[] = {
    { "mpegts/input/network_list", ACCESS_ADMIN, api_mpegts_input_network_list, NULL },
    { "mpegts/network/grid",       ACCESS_ADMIN, api_idnode_grid,  api_mpegts_network_grid },
    { "mpegts/network/class",      ACCESS_ADMIN, api_idnode_class, (void*)&mpegts_network_class },
    { "mpegts/network/builders",   ACCESS_ADMIN, api_mpegts_network_builders, NULL },
    { "mpegts/network/create",     ACCESS_ADMIN, api_mpegts_network_create,   NULL },
    { "mpegts/network/mux_class",  ACCESS_ADMIN, api_mpegts_network_muxclass, NULL },
    { "mpegts/network/mux_create", ACCESS_ADMIN, api_mpegts_network_muxcreate, NULL },
    { "mpegts/network/scan",       ACCESS_ADMIN, api_mpegts_network_scan, NULL },
    { "mpegts/mux/grid",           ACCESS_ADMIN, api_idnode_grid,  api_mpegts_mux_grid },
    { "mpegts/mux/class",          ACCESS_ADMIN, api_idnode_class, (void*)&mpegts_mux_class },
    { "mpegts/service/grid",       ACCESS_ADMIN, api_idnode_grid,  api_mpegts_service_grid },
    { "mpegts/service/class",      ACCESS_ADMIN, api_idnode_class, (void*)&mpegts_service_class },
    { "mpegts/mux_sched/class",    ACCESS_ADMIN, api_idnode_class, (void*)&mpegts_mux_sched_class },
    { "mpegts/mux_sched/grid",     ACCESS_ADMIN, api_idnode_grid, api_mpegts_mux_sched_grid },
    { "mpegts/mux_sched/create",   ACCESS_ADMIN, api_mpegts_mux_sched_create, NULL },
#if ENABLE_MPEGTS_DVB
    { "dvb/orbitalpos/list",       ACCESS_ADMIN, api_dvb_orbitalpos_list, NULL },
    { "dvb/scanfile/list",         ACCESS_ADMIN, api_dvb_scanfile_list, NULL },
#endif
    { NULL },
  };
