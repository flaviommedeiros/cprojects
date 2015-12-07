while ((c = getopt_long (argc, argv,
#else
	while ((c = getopt (argc, argv,
#endif
@for $key, $info in $parameters.items()
@if $info.get('opt'):
@if $info.get('type') == 'boolean':
	@if not isinstance($info.get('opt'), int):
		"$info.get('opt')"
	@end if
@else:
	@if not isinstance($info.get('opt'), int):
		"$info.get('opt'):"
	@end if
@end if
@end if
@end for
#ifdef _GNU_SOURCE
		, long_options, NULL
#endif
		)) != -1)
	{
		switch (c)
		{
			case 500:
				retval |= 1;
				break;
			case 501:
				retval |= 2;
				break;
@for $key, $info in $parameters.items()
	@if $info.get('opt'):
		@if isinstance($info.get('opt'), int):
			case $info.get("opt"):
		@else:
			case '$info.get("opt")':
		@end if
		@if $info.get('range')
				{
					$support.typeof(info) check;
					char *endptr;
					errno = 0;
					check = strtol(optarg, &endptr, 10);
					if ((errno == ERANGE
							&& (check == LONG_MAX || check == LONG_MIN))
							|| (errno != 0 && check == 0))
					{
						retval |= 4;
						break;
					}
					if (endptr == optarg)
					{
						retval |= 8;
						break;
					}
					if (check < $support.min(info))
					{
						retval |= 16;
						break;
					}
					if (check > $support.max(info))
					{
						retval |= 32;
						break;
					}
				}
		@end if
		@if $support.isenum(info):
				if (!(
				   !strcmp(optarg, "${support.enumval(info)[0]}")
			@for $enum in $support.enumval(info)[1:]
				   || !strcmp(optarg, "$enum")
			@end for
				  ))
				{
					retval |= 64;
					break;
				}
		@end if
				found = ksLookupByName(ks, "$support.userkey(key)", 0);
				if (!found)
				{
					ksAppendKey(ks, keyNew("$support.userkey(key)",
							KEY_VALUE, $optarg(info),
							KEY_END));
				}
				else
				{
					keySetString(found, $optarg(info));
				}
				break;
	@end if
@end for
			case '?':
				retval |= 128;
				break;
			default:
				retval |= 256;
				break;
/*
			case '?':
				if (optopt == 'c')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr,
							"Unknown option character `\\x%x'.\n",
							optopt);
				return 1;
*/
		}
	}
	return retval;
}

#ifdef __cplusplus
}
//extern "C"
#endif
$util.footer($args.output)
