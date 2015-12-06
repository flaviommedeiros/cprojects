static struct opt_table opt_cmdline_table[] = {
	OPT_WITH_ARG("--config|-c",
		     load_config, NULL, NULL,
		     "Load a JSON-format configuration file\n"
		     "See example.conf for an example configuration."),
	OPT_EARLY_WITHOUT_ARG("--no-config",
	                opt_set_bool, &config_loaded,
	                opt_hidden),
	OPT_EARLY_WITHOUT_ARG("--no-default-config",
	                opt_set_bool, &config_loaded,
	                "Inhibit loading default config file"),
	OPT_WITHOUT_ARG("--default-config",
	                load_default_config, NULL,
	                "Always load the default config file"),
	OPT_WITHOUT_ARG("--help|-h",
			opt_verusage_and_exit, NULL,
			"Print this message"),
#ifdef USE_OPENCL
	OPT_WITHOUT_ARG("--ndevs|-n",
			print_ndevs_and_exit, &nDevs,
			opt_hidden),
#endif
	OPT_WITHOUT_ARG("--version|-V",
			my_opt_version_and_exit, NULL,
			"Display version and exit"),
	OPT_ENDTABLE
};
