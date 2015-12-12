static GladeWidgetInitData gnome_page[] =
{
  { "GnomeApp", gb_gnome_app_init },
  { "GnomeDruid", gb_gnome_druid_init },
  { "GnomeCanvas", gb_gnome_canvas_init },
  { "GnomeIconSelection", gb_gnome_icon_selection_init },

  { "GnomeIconEntry", gb_gnome_icon_entry_init },
  { "GnomeHRef", gb_gnome_href_init },
  { "GnomeDateEdit", gb_gnome_date_edit_init },
  { "GnomeAppBar", gb_gnome_appbar_init },


#if 0
  { "GnomePaperSelector", gb_gnome_paper_selector_init },
#endif


  { "BonoboWidget", gb_bonobo_control_init },

  { NULL, NULL }
};
