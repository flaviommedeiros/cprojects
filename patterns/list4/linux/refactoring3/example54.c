switch (params.command) {
	case 'l':
		if (params.uprobes) {
			pr_err("  Error: Don't use --list with --exec.\n");
			parse_options_usage(probe_usage, options, "l", true);
			parse_options_usage(NULL, options, "x", true);
			return -EINVAL;
		}
		ret = show_perf_probe_events(params.filter);
		if (ret < 0)
			pr_err_with_code("  Error: Failed to show event list.", ret);
		return ret;
	case 'F':
		ret = show_available_funcs(params.target, params.filter,
					params.uprobes);
		if (ret < 0)
			pr_err_with_code("  Error: Failed to show functions.", ret);
		return ret;
#ifdef HAVE_DWARF_SUPPORT
	case 'L':
		ret = show_line_range(&params.line_range, params.target,
				      params.uprobes);
		if (ret < 0)
			pr_err_with_code("  Error: Failed to show lines.", ret);
		return ret;
	case 'V':
		if (!params.filter)
			params.filter = strfilter__new(DEFAULT_VAR_FILTER,
						       NULL);

		ret = show_available_vars(params.events, params.nevents,
					  params.filter);
		if (ret < 0)
			pr_err_with_code("  Error: Failed to show vars.", ret);
		return ret;
#endif
	case 'd':
		ret = perf_del_probe_events(params.filter);
		if (ret < 0) {
			pr_err_with_code("  Error: Failed to delete events.", ret);
			return ret;
		}
		break;
	case 'a':
		/* Ensure the last given target is used */
		if (params.target && !params.target_used) {
			pr_err("  Error: -x/-m must follow the probe definitions.\n");
			parse_options_usage(probe_usage, options, "m", true);
			parse_options_usage(NULL, options, "x", true);
			return -EINVAL;
		}

		ret = perf_add_probe_events(params.events, params.nevents);
		if (ret < 0) {
			pr_err_with_code("  Error: Failed to add events.", ret);
			return ret;
		}
		break;
	default:
		usage_with_options(probe_usage, options);
	}
