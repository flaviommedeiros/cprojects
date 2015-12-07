#ifndef ENABLE_STRICT_OPTIONS_CHECK
if (strncmp (actual, expected, 2))
	{
	  msg (D_SHOW_OCC, "NOTE: Options consistency check may be skewed by version differences");
	  options_warning_safe_ml (D_SHOW_OCC, actual, expected, actual_n);
	}
      else
#endif
	ret = !strcmp (actual, expected);
