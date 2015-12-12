static const struct option longopts[] = {
		{ "id",		   optional_argument, 0, OPT_ID		   },
		{ "stderr",	   no_argument,	      0, 's'		   },
		{ "file",	   required_argument, 0, 'f'		   },
		{ "no-act",        no_argument,       0, OPT_NOACT,	   },
		{ "priority",	   required_argument, 0, 'p'		   },
		{ "tag",	   required_argument, 0, 't'		   },
		{ "socket",	   required_argument, 0, 'u'		   },
		{ "socket-errors", required_argument, 0, OPT_SOCKET_ERRORS },
		{ "udp",	   no_argument,	      0, 'd'		   },
		{ "tcp",	   no_argument,	      0, 'T'		   },
		{ "server",	   required_argument, 0, 'n'		   },
		{ "port",	   required_argument, 0, 'P'		   },
		{ "version",	   no_argument,	      0, 'V'		   },
		{ "help",	   no_argument,	      0, 'h'		   },
		{ "octet-count",   no_argument,	      0, OPT_OCTET_COUNT   },
		{ "prio-prefix",   no_argument,	      0, OPT_PRIO_PREFIX   },
		{ "rfc3164",	   no_argument,	      0, OPT_RFC3164	   },
		{ "rfc5424",	   optional_argument, 0, OPT_RFC5424	   },
		{ "size",	   required_argument, 0, 'S'		   },
		{ "msgid",	   required_argument, 0, OPT_MSGID	   },
		{ "skip-empty",	   no_argument,	      0, 'e'		   },
		{ "sd-id",         required_argument, 0, OPT_STRUCTURED_DATA_ID          },
		{ "sd-param",      required_argument, 0, OPT_STRUCTURED_DATA_PARAM       },
#ifdef HAVE_LIBSYSTEMD
		{ "journald",	   optional_argument, 0, OPT_JOURNALD	   },
#endif
		{ NULL,		   0,		      0, 0		   }
	};
