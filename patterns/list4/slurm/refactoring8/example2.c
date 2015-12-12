GtkToggleActionEntry toggle_entries[] = {
		{"grid", GTK_STOCK_SELECT_COLOR, "Show _Grid",
		 "<control>g", "Visual display of cluster",
		 G_CALLBACK(_set_grid), working_sview_config.show_grid},
		{"hidden", GTK_STOCK_SELECT_COLOR, "Show _Hidden",
		 "<control>h", "Display Hidden Partitions/Jobs",
		 G_CALLBACK(_set_hidden), working_sview_config.show_hidden},
		{"page_opts", GTK_STOCK_SELECT_COLOR, "Save Page Options",
		 "<control>w", "Save Page Options",
		 G_CALLBACK(_set_page_opts),
		 working_sview_config.save_page_opts},
#ifdef WANT_TOPO_ON_MAIN_OPTIONS
		{"topoorder", GTK_STOCK_SELECT_COLOR, "Set Topology Grid",
		 "<control>t", "Set Topology Grid",
		 G_CALLBACK(_set_topogrid),
		 working_sview_config.grid_topological},
#endif
		{"ruled", GTK_STOCK_SELECT_COLOR, "R_uled Tables",
		 "<control>u", "Have ruled tables or not",
		 G_CALLBACK(_set_ruled), working_sview_config.ruled_treeview},
		{"admin", GTK_STOCK_PREFERENCES,
		 "_Admin Mode", "<control>a",
		 "Allows user to change or update information",
		 G_CALLBACK(_set_admin_mode),
		 working_sview_config.admin_mode}
	};
