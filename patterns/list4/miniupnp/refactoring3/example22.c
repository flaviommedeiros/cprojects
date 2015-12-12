switch(argv[i][1])
		{
		case 'b':
			if(i+1 < argc) {
				upnp_bootid = (unsigned int)strtoul(argv[++i], NULL, 10);
			} else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
		case 'o':
			if(i+1 < argc)
				use_ext_ip_addr = argv[++i];
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
		case 't':
			if(i+1 < argc)
				v->notify_interval = atoi(argv[++i]);
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
		case 'r':
			if(i+1 < argc)
				v->clean_ruleset_interval = atoi(argv[++i]);
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
		case 'u':
			if(i+1 < argc) {
				strncpy(uuidvalue_igd+5, argv[++i], strlen(uuidvalue_igd+5) + 1);
				complete_uuidvalues();
			} else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
#ifdef ENABLE_MANUFACTURER_INFO_CONFIGURATION
		case 'z':
			if(i+1 < argc)
				strncpy(friendly_name, argv[++i], FRIENDLY_NAME_MAX_LEN);
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			friendly_name[FRIENDLY_NAME_MAX_LEN-1] = '\0';
			break;
#endif	/* ENABLE_MANUFACTURER_INFO_CONFIGURATION */
		case 's':
			if(i+1 < argc)
				strncpy(serialnumber, argv[++i], SERIALNUMBER_MAX_LEN);
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			serialnumber[SERIALNUMBER_MAX_LEN-1] = '\0';
			break;
		case 'm':
			if(i+1 < argc)
				strncpy(modelnumber, argv[++i], MODELNUMBER_MAX_LEN);
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			modelnumber[MODELNUMBER_MAX_LEN-1] = '\0';
			break;
#ifdef ENABLE_NATPMP
		case 'N':
			/*enablenatpmp = 1;*/
			SETFLAG(ENABLENATPMPMASK);
			break;
#endif	/* ENABLE_NATPMP */
		case 'U':
			/*sysuptime = 1;*/
			SETFLAG(SYSUPTIMEMASK);
			break;
		/*case 'l':
			logfilename = argv[++i];
			break;*/
#if defined(USE_PF) || defined(USE_IPF)
		case 'L':
			/*logpackets = 1;*/
			SETFLAG(LOGPACKETSMASK);
			break;
#endif	/* defined(USE_PF) || defined(USE_IPF) */
		case 'S':
			SETFLAG(SECUREMODEMASK);
			break;
		case 'i':
			if(i+1 < argc)
				ext_if_name = argv[++i];
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
#ifdef USE_PF
		case 'q':
			if(i+1 < argc)
				queue = argv[++i];
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
		case 'T':
			if(i+1 < argc)
				tag = argv[++i];
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
#endif	/* USE_PF */
		case 'p':
			if(i+1 < argc)
				v->port = atoi(argv[++i]);
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
#ifdef ENABLE_HTTPS
		case 'H':
			if(i+1 < argc)
				v->https_port = atoi(argv[++i]);
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
#endif	/* ENABLE_HTTPS */
#ifdef ENABLE_NFQUEUE
		case 'Q':
			if(i+1<argc)
			{
				nfqueue = atoi(argv[++i]);
			}
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
		case 'n':
			if (i+1 < argc) {
				i++;
				if(n_nfqix < MAX_LAN_ADDR) {
					nfqix[n_nfqix++] = if_nametoindex(argv[i]);
				} else {
					fprintf(stderr,"Too many nfq interfaces. Ignoring %s\n", argv[i]);
				}
			} else {
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			}
			break;
#endif	/* ENABLE_NFQUEUE */
		case 'P':
			if(i+1 < argc)
				pidfilename = argv[++i];
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
		case 'd':
			debug_flag = 1;
			break;
		case 'w':
			if(i+1 < argc)
				presurl = argv[++i];
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
		case 'B':
			if(i+2<argc)
			{
				downstream_bitrate = strtoul(argv[++i], 0, 0);
				upstream_bitrate = strtoul(argv[++i], 0, 0);
			}
			else
				fprintf(stderr, "Option -%c takes two arguments.\n", argv[i][1]);
			break;
		case 'a':
#ifndef MULTIPLE_EXTERNAL_IP
			if(i+1 < argc)
			{
				i++;
				lan_addr = (struct lan_addr_s *) malloc(sizeof(struct lan_addr_s));
				if (lan_addr == NULL)
				{
					fprintf(stderr, "malloc(sizeof(struct lan_addr_s)): %m");
					break;
				}
				if(parselanaddr(lan_addr, argv[i]) != 0)
				{
					fprintf(stderr, "can't parse \"%s\" as a valid "
#ifndef ENABLE_IPV6
					        "LAN address or "
#endif	/* #ifndef ENABLE_IPV6 */
					        "interface name\n", argv[i]);
					free(lan_addr);
					break;
				}
				/* check if we already have this address */
				for(lan_addr2 = lan_addrs.lh_first; lan_addr2 != NULL; lan_addr2 = lan_addr2->list.le_next)
				{
					if (0 == strncmp(lan_addr2->str, lan_addr->str, 15))
						break;
				}
				if (lan_addr2 == NULL)
					LIST_INSERT_HEAD(&lan_addrs, lan_addr, list);
			}
			else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
#else	/* #ifndef MULTIPLE_EXTERNAL_IP */
			if(i+2 < argc)
			{
				char *val=calloc((strlen(argv[i+1]) + strlen(argv[i+2]) + 1), sizeof(char));
				if (val == NULL)
				{
					fprintf(stderr, "memory allocation error for listen address storage\n");
					break;
				}
				sprintf(val, "%s %s", argv[i+1], argv[i+2]);

				lan_addr = (struct lan_addr_s *) malloc(sizeof(struct lan_addr_s));
				if (lan_addr == NULL)
				{
					fprintf(stderr, "malloc(sizeof(struct lan_addr_s)): %m");
					free(val);
					break;
				}
				if(parselanaddr(lan_addr, val) != 0)
				{
					fprintf(stderr, "can't parse \"%s\" as a valid LAN address or interface name\n", val);
					free(lan_addr);
					free(val);
					break;
				}
				/* check if we already have this address */
				for(lan_addr2 = lan_addrs.lh_first; lan_addr2 != NULL; lan_addr2 = lan_addr2->list.le_next)
				{
					if (0 == strncmp(lan_addr2->str, lan_addr->str, 15))
						break;
				}
				if (lan_addr2 == NULL)
					LIST_INSERT_HEAD(&lan_addrs, lan_addr, list);

				free(val);
				i+=2;
			}
			else
				fprintf(stderr, "Option -%c takes two arguments.\n", argv[i][1]);
#endif 	/* #ifndef MULTIPLE_EXTERNAL_IP */
			break;
		case 'A':
			if(i+1 < argc) {
				void * tmp;
				tmp = realloc(upnppermlist, sizeof(struct upnpperm) * (num_upnpperm+1));
				if(tmp == NULL) {
					fprintf(stderr, "memory allocation error for permission\n");
				} else {
					upnppermlist = tmp;
					if(read_permission_line(upnppermlist + num_upnpperm, argv[++i]) >= 0) {
						num_upnpperm++;
					} else {
						fprintf(stderr, "Permission rule parsing error :\n%s\n", argv[i]);
					}
				}
			} else
				fprintf(stderr, "Option -%c takes one argument.\n", argv[i][1]);
			break;
		case 'f':
			i++;	/* discarding, the config file is already read */
			break;
		default:
			fprintf(stderr, "Unknown option: %s\n", argv[i]);
		}
