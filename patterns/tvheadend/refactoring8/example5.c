const idclass_t mpegts_network_class =
{
  .ic_class      = "mpegts_network",
  .ic_caption    = N_("MPEG-TS network"),
  .ic_event      = "mpegts_network",
  .ic_perm_def   = ACCESS_ADMIN,
  .ic_save       = mpegts_network_class_save,
  .ic_get_title  = mpegts_network_class_get_title,
  .ic_properties = (const property_t[]){
    {
      .type     = PT_STR,
      .id       = "networkname",
      .name     = N_("Network name"),
      .off      = offsetof(mpegts_network_t, mn_network_name),
      .notify   = idnode_notify_title_changed,
    },
    {
      .type     = PT_U16,
      .id       = "nid",
      .name     = N_("Network ID (limit scanning)"),
      .opts     = PO_ADVANCED,
      .off      = offsetof(mpegts_network_t, mn_nid),
    },
    {
      .type     = PT_BOOL,
      .id       = "autodiscovery",
      .name     = N_("Network discovery"),
      .off      = offsetof(mpegts_network_t, mn_autodiscovery),
      .def.i    = 1
    },
    {
      .type     = PT_BOOL,
      .id       = "skipinitscan",
      .name     = N_("Skip initial scan"),
      .off      = offsetof(mpegts_network_t, mn_skipinitscan),
      .def.i    = 1
    },
    {
      .type     = PT_BOOL,
      .id       = "idlescan",
      .name     = N_("Idle scan muxes"),
      .off      = offsetof(mpegts_network_t, mn_idlescan),
      .def.i    = 0,
      .notify   = mpegts_network_class_idlescan_notify,
      .opts     = PO_ADVANCED | PO_HIDDEN,
    },
    {
      .type     = PT_BOOL,
      .id       = "sid_chnum",
      .name     = N_("Use service IDs as channel numbers"),
      .off      = offsetof(mpegts_network_t, mn_sid_chnum),
      .def.i    = 0,
    },
    {
      .type     = PT_BOOL,
      .id       = "ignore_chnum",
      .name     = N_("Ignore provider's channel numbers"),
      .off      = offsetof(mpegts_network_t, mn_ignore_chnum),
      .def.i    = 0,
    },
#if ENABLE_SATIP_SERVER
    {
      .type     = PT_U16,
      .id       = "satip_source",
      .name     = N_("SAT>IP source number"),
      .off      = offsetof(mpegts_network_t, mn_satip_source),
    },
#endif
    {
      .type     = PT_STR,
      .id       = "charset",
      .name     = N_("Character set"),
      .off      = offsetof(mpegts_network_t, mn_charset),
      .list     = dvb_charset_enum,
      .opts     = PO_ADVANCED,
    },
    {
      .type     = PT_BOOL,
      .id       = "localtime",
      .name     = N_("EIT broadcast in local time"),
      .off      = offsetof(mpegts_network_t, mn_localtime),
      .opts     = PO_ADVANCED,
    },
    {
      .type     = PT_INT,
      .id       = "num_mux",
      .name     = N_("# Muxes"),
      .opts     = PO_RDONLY | PO_NOSAVE,
      .get      = mpegts_network_class_get_num_mux,
    },
    {
      .type     = PT_INT,
      .id       = "num_svc",
      .name     = N_("# Services"),
      .opts     = PO_RDONLY | PO_NOSAVE,
      .get      = mpegts_network_class_get_num_svc,
    },
    {
      .type     = PT_INT,
      .id       = "num_chn",
      .name     = N_("# Mapped channels"),
      .opts     = PO_RDONLY | PO_NOSAVE,
      .get      = mpegts_network_class_get_num_chn,
    },
    {
      .type     = PT_INT,
      .id       = "scanq_length",
      .name     = N_("Scan queue length"),
      .opts     = PO_RDONLY | PO_NOSAVE,
      .get      = mpegts_network_class_get_scanq_length,
    },
    {}
  }
};
