switch (op) {

		case 'a':
			/* compatibility for old -a */
			break;

		case 'A':
			++ndo->ndo_Aflag;
			break;

		case 'b':
			++ndo->ndo_bflag;
			break;

#if defined(HAVE_PCAP_CREATE) || defined(_WIN32)
		case 'B':
			Bflag = atoi(optarg)*1024;
			if (Bflag <= 0)
				error("invalid packet buffer size %s", optarg);
			break;
#endif /* defined(HAVE_PCAP_CREATE) || defined(_WIN32) */

		case 'c':
			cnt = atoi(optarg);
			if (cnt <= 0)
				error("invalid packet count %s", optarg);
			break;

		case 'C':
			Cflag = atoi(optarg) * 1000000;
			if (Cflag < 0)
				error("invalid file size %s", optarg);
			break;

		case 'd':
			++dflag;
			break;

		case 'D':
			Dflag++;
			break;

		case 'L':
			Lflag++;
			break;

		case 'e':
			++ndo->ndo_eflag;
			break;

		case 'E':
#ifndef HAVE_LIBCRYPTO
			warning("crypto code not compiled in");
#endif
			ndo->ndo_espsecret = optarg;
			break;

		case 'f':
			++ndo->ndo_fflag;
			break;

		case 'F':
			infile = optarg;
			break;

		case 'G':
			Gflag = atoi(optarg);
			if (Gflag < 0)
				error("invalid number of seconds %s", optarg);

                        /* We will create one file initially. */
                        Gflag_count = 0;

			/* Grab the current time for rotation use. */
			if ((Gflag_time = time(NULL)) == (time_t)-1) {
				error("main: can't get current time: %s",
				    pcap_strerror(errno));
			}
			break;

		case 'h':
			print_usage();
			exit(0);
			break;

		case 'H':
			++ndo->ndo_Hflag;
			break;

		case 'i':
			if (optarg[0] == '0' && optarg[1] == 0)
				error("Invalid adapter index");

#ifdef HAVE_PCAP_FINDALLDEVS
			/*
			 * If the argument is a number, treat it as
			 * an index into the list of adapters, as
			 * printed by "tcpdump -D".
			 *
			 * This should be OK on UNIX systems, as interfaces
			 * shouldn't have names that begin with digits.
			 * It can be useful on Windows, where more than
			 * one interface can have the same name.
			 */
			devnum = strtol(optarg, &end, 10);
			if (optarg != end && *end == '\0') {
				if (devnum < 0)
					error("Invalid adapter index");

				if (pcap_findalldevs(&devlist, ebuf) < 0)
					error("%s", ebuf);
				/*
				 * Look for the devnum-th entry in the
				 * list of devices (1-based).
				 */
				for (i = 0, dev = devlist;
				    i < devnum-1 && dev != NULL;
				    i++, dev = dev->next)
					;
				if (dev == NULL)
					error("Invalid adapter index");
				device = strdup(dev->name);
				pcap_freealldevs(devlist);
				break;
			}
#endif /* HAVE_PCAP_FINDALLDEVS */
			device = optarg;
			break;

#ifdef HAVE_PCAP_CREATE
		case 'I':
			++Iflag;
			break;
#endif /* HAVE_PCAP_CREATE */

#ifdef HAVE_PCAP_SET_TSTAMP_TYPE
		case 'j':
			jflag = pcap_tstamp_type_name_to_val(optarg);
			if (jflag < 0)
				error("invalid time stamp type %s", optarg);
			break;

		case 'J':
			Jflag++;
			break;
#endif

		case 'l':
#ifdef _WIN32
			/*
			 * _IOLBF is the same as _IOFBF in Microsoft's C
			 * libraries; the only alternative they offer
			 * is _IONBF.
			 *
			 * XXX - this should really be checking for MSVC++,
			 * not _WIN32, if, for example, MinGW has its own
			 * C library that is more UNIX-compatible.
			 */
			setvbuf(stdout, NULL, _IONBF, 0);
#else /* _WIN32 */
#ifdef HAVE_SETLINEBUF
			setlinebuf(stdout);
#else
			setvbuf(stdout, NULL, _IOLBF, 0);
#endif
#endif /* _WIN32 */
			break;

		case 'K':
			++ndo->ndo_Kflag;
			break;

		case 'm':
#ifdef USE_LIBSMI
			if (smiLoadModule(optarg) == 0) {
				error("could not load MIB module %s", optarg);
			}
			ndo->ndo_mflag = 1;
#else
			(void)fprintf(stderr, "%s: ignoring option `-m %s' ",
				      program_name, optarg);
			(void)fprintf(stderr, "(no libsmi support)\n");
#endif
			break;

		case 'M':
			/* TCP-MD5 shared secret */
#ifndef HAVE_LIBCRYPTO
			warning("crypto code not compiled in");
#endif
			ndo->ndo_sigsecret = optarg;
			break;

		case 'n':
			++ndo->ndo_nflag;
			break;

		case 'N':
			++ndo->ndo_Nflag;
			break;

		case 'O':
			Oflag = 0;
			break;

		case 'p':
			++pflag;
			break;

		case 'q':
			++ndo->ndo_qflag;
			++ndo->ndo_suppress_default_print;
			break;

#ifdef HAVE_PCAP_SETDIRECTION
		case 'Q':
			if (ascii_strcasecmp(optarg, "in") == 0)
				Qflag = PCAP_D_IN;
			else if (ascii_strcasecmp(optarg, "out") == 0)
				Qflag = PCAP_D_OUT;
			else if (ascii_strcasecmp(optarg, "inout") == 0)
				Qflag = PCAP_D_INOUT;
			else
				error("unknown capture direction `%s'", optarg);
			break;
#endif /* HAVE_PCAP_SETDIRECTION */

		case 'r':
			RFileName = optarg;
			break;

		case 's':
			ndo->ndo_snaplen = strtol(optarg, &end, 0);
			if (optarg == end || *end != '\0'
			    || ndo->ndo_snaplen < 0 || ndo->ndo_snaplen > MAXIMUM_SNAPLEN)
				error("invalid snaplen %s", optarg);
			else if (ndo->ndo_snaplen == 0)
				ndo->ndo_snaplen = MAXIMUM_SNAPLEN;
			break;

		case 'S':
			++ndo->ndo_Sflag;
			break;

		case 't':
			++ndo->ndo_tflag;
			break;

		case 'T':
			if (ascii_strcasecmp(optarg, "vat") == 0)
				ndo->ndo_packettype = PT_VAT;
			else if (ascii_strcasecmp(optarg, "wb") == 0)
				ndo->ndo_packettype = PT_WB;
			else if (ascii_strcasecmp(optarg, "rpc") == 0)
				ndo->ndo_packettype = PT_RPC;
			else if (ascii_strcasecmp(optarg, "rtp") == 0)
				ndo->ndo_packettype = PT_RTP;
			else if (ascii_strcasecmp(optarg, "rtcp") == 0)
				ndo->ndo_packettype = PT_RTCP;
			else if (ascii_strcasecmp(optarg, "snmp") == 0)
				ndo->ndo_packettype = PT_SNMP;
			else if (ascii_strcasecmp(optarg, "cnfp") == 0)
				ndo->ndo_packettype = PT_CNFP;
			else if (ascii_strcasecmp(optarg, "tftp") == 0)
				ndo->ndo_packettype = PT_TFTP;
			else if (ascii_strcasecmp(optarg, "aodv") == 0)
				ndo->ndo_packettype = PT_AODV;
			else if (ascii_strcasecmp(optarg, "carp") == 0)
				ndo->ndo_packettype = PT_CARP;
			else if (ascii_strcasecmp(optarg, "radius") == 0)
				ndo->ndo_packettype = PT_RADIUS;
			else if (ascii_strcasecmp(optarg, "zmtp1") == 0)
				ndo->ndo_packettype = PT_ZMTP1;
			else if (ascii_strcasecmp(optarg, "vxlan") == 0)
				ndo->ndo_packettype = PT_VXLAN;
			else if (ascii_strcasecmp(optarg, "pgm") == 0)
				ndo->ndo_packettype = PT_PGM;
			else if (ascii_strcasecmp(optarg, "pgm_zmtp1") == 0)
				ndo->ndo_packettype = PT_PGM_ZMTP1;
			else if (ascii_strcasecmp(optarg, "lmp") == 0)
				ndo->ndo_packettype = PT_LMP;
			else
				error("unknown packet type `%s'", optarg);
			break;

		case 'u':
			++ndo->ndo_uflag;
			break;

#ifdef HAVE_PCAP_DUMP_FLUSH
		case 'U':
			++Uflag;
			break;
#endif

		case 'v':
			++ndo->ndo_vflag;
			break;

		case 'V':
			VFileName = optarg;
			break;

		case 'w':
			WFileName = optarg;
			break;

		case 'W':
			Wflag = atoi(optarg);
			if (Wflag < 0)
				error("invalid number of output files %s", optarg);
			WflagChars = getWflagChars(Wflag);
			break;

		case 'x':
			++ndo->ndo_xflag;
			++ndo->ndo_suppress_default_print;
			break;

		case 'X':
			++ndo->ndo_Xflag;
			++ndo->ndo_suppress_default_print;
			break;

		case 'y':
			yflag_dlt_name = optarg;
			yflag_dlt =
				pcap_datalink_name_to_val(yflag_dlt_name);
			if (yflag_dlt < 0)
				error("invalid data link type %s", yflag_dlt_name);
			break;

#if defined(HAVE_PCAP_DEBUG) || defined(HAVE_YYDEBUG)
		case 'Y':
			{
			/* Undocumented flag */
#ifdef HAVE_PCAP_DEBUG
			extern int pcap_debug;
			pcap_debug = 1;
#else
			extern int yydebug;
			yydebug = 1;
#endif
			}
			break;
#endif
		case 'z':
			zflag = strdup(optarg);
			if (zflag == NULL)
				error("Unable to allocate memory for -z argument");
			break;

		case 'Z':
			username = strdup(optarg);
			if (username == NULL)
				error("Unable to allocate memory for -Z argument");
			break;

		case '#':
			ndo->ndo_packet_number = 1;
			break;

		case OPTION_VERSION:
			print_version();
			exit(0);
			break;

#ifdef HAVE_PCAP_SET_TSTAMP_PRECISION
		case OPTION_TSTAMP_PRECISION:
			ndo->ndo_tstamp_precision = tstamp_precision_from_string(optarg);
			if (ndo->ndo_tstamp_precision < 0)
				error("unsupported time stamp precision");
			break;
#endif

#ifdef HAVE_PCAP_SET_IMMEDIATE_MODE
		case OPTION_IMMEDIATE_MODE:
			immediate_mode = 1;
			break;
#endif

		default:
			print_usage();
			exit(1);
			/* NOTREACHED */
		}
