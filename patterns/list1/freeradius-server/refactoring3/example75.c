switch (opt) {
		case 'a':
		{
			pcap_if_t *all_devices = NULL;
			pcap_if_t *dev_p;

			if (pcap_findalldevs(&all_devices, errbuf) < 0) {
				ERROR("Error getting available capture devices: %s", errbuf);
				goto finish;
			}

			int i = 1;
			for (dev_p = all_devices;
			     dev_p;
			     dev_p = dev_p->next) {
				INFO("%i.%s", i++, dev_p->name);
			}
			ret = 0;
			goto finish;
		}

		/* super secret option */
		case 'b':
			conf->buffer_pkts = atoi(optarg);
			if (conf->buffer_pkts == 0) {
				ERROR("Invalid buffer length \"%s\"", optarg);
				usage(1);
			}
			break;

		case 'c':
			conf->limit = atoi(optarg);
			if (conf->limit == 0) {
				ERROR("Invalid number of packets \"%s\"", optarg);
				usage(1);
			}
			break;

		/* udp checksum */
		case 'C':
			conf->verify_udp_checksum = true;
			break;

		case 'd':
			radius_dir = optarg;
			break;

		case 'D':
			dict_dir = optarg;
			break;

		case 'e':
			if (rs_build_event_flags((int *) &conf->event_flags, rs_events, optarg) < 0) {
				usage(64);
			}
			break;

		case 'E':
			conf->stats.out = RS_STATS_OUT_STDIO_CSV;
			break;

		case 'f':
			conf->pcap_filter = optarg;
			break;

		case 'h':
			usage(0);	/* never returns */

		case 'i':
			*in_head = fr_pcap_init(conf, optarg, PCAP_INTERFACE_IN);
			if (!*in_head) goto finish;
			in_head = &(*in_head)->next;
			conf->from_dev = true;
			break;

		case 'I':
			*in_head = fr_pcap_init(conf, optarg, PCAP_FILE_IN);
			if (!*in_head) {
				goto finish;
			}
			in_head = &(*in_head)->next;
			conf->from_file = true;
			break;

		case 'l':
			conf->list_attributes = optarg;
			break;

		case 'L':
			conf->link_attributes = optarg;
			break;

		case 'm':
			conf->promiscuous = false;
			break;

		case 'p':
			port = atoi(optarg);
			break;

		case 'P':
			conf->daemonize = true;
			conf->pidfile = optarg;
			break;

		case 'q':
			if (fr_debug_lvl > 0) {
				fr_debug_lvl--;
			}
			break;

		case 'r':
			conf->filter_request = optarg;
			break;

		case 'R':
			conf->filter_response = optarg;
			break;

		case 's':
			conf->radius_secret = optarg;
			break;

		case 'S':
			conf->to_stdout = true;
			break;

		case 'v':
#ifdef HAVE_COLLECTDC_H
			INFO("%s, %s, collectdclient version %s", radsniff_version, pcap_lib_version(),
			     lcc_version_string());
#else
			INFO("%s %s", radsniff_version, pcap_lib_version());
#endif
			exit(EXIT_SUCCESS);

		case 'w':
			out = fr_pcap_init(conf, optarg, PCAP_FILE_OUT);
			if (!out) {
				ERROR("Failed creating pcap file \"%s\"", optarg);
				exit(EXIT_FAILURE);
			}
			conf->to_file = true;
			break;

		case 'x':
		case 'X':
			fr_debug_lvl++;
			break;

		case 'W':
			conf->stats.interval = atoi(optarg);
			conf->print_packet = false;
			if (conf->stats.interval <= 0) {
				ERROR("Stats interval must be > 0");
				usage(64);
			}
			break;

		case 'T':
			conf->stats.timeout = atoi(optarg);
			if (conf->stats.timeout <= 0) {
				ERROR("Timeout value must be > 0");
				usage(64);
			}
			break;

#ifdef HAVE_COLLECTDC_H
		case 'N':
			conf->stats.prefix = optarg;
			break;

		case 'O':
			conf->stats.collectd = optarg;
			conf->stats.out = RS_STATS_OUT_COLLECTD;
			break;
#endif
		default:
			usage(64);
		}
