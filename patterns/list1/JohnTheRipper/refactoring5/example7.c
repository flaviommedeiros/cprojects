#ifndef DYNAMIC_DISABLED
if (!strncasecmp(options.format, "dynamic=", 8) &&
			    !strcasecmp(format->params.label, "dynamic=")) {
				DC_HANDLE H;
				if (!dynamic_compile(options.format, &H)) {
					if (dynamic_assign_script_to_format(
						    H, format))
						return;
				} else
					return;
			} else
#endif
				return;
