switch (c) {
	case '4':
		ctl->cmsg(CMSG_ERROR, VERB_NORMAL,
				"-4 option is obsoleted.  Please use -N");
		return 1;
	case 'A':
		if (*optarg != ',' && *optarg != 'a')
			err += parse_opt_A(optarg);
		if (strchr(optarg, ','))
			err += parse_opt_drum_power(strchr(optarg, ',') + 1);
		if (strchr(optarg, 'a'))
			opt_amp_compensation = 1;
		return err;
	case 'a':
		antialiasing_allowed = 1;
		break;
	case 'B':
		return parse_opt_B(optarg);
	case 'C':
		return parse_opt_C(optarg);
	case 'c':
		return parse_opt_c(optarg);
	case 'D':
		return parse_opt_D(optarg);
	case 'd':
		return parse_opt_d(optarg);
	case 'E':
		return parse_opt_E(optarg);
	case 'e':
		return parse_opt_e(optarg);
	case 'F':
		adjust_panning_immediately = (adjust_panning_immediately) ? 0 : 1;
		break;
	case 'f':
		fast_decay = (fast_decay) ? 0 : 1;
		break;
	case 'g':
		return parse_opt_g(optarg);
	case 'H':
		return parse_opt_H(optarg);
	case 'h':
		return parse_opt_h(optarg);
	case 'I':
		ctl->cmsg(CMSG_ERROR, VERB_NORMAL,
				"-I option is obsoleted.  Please use -Ei");
		return 1;
	case 'i':
		return parse_opt_i(optarg);
	case 'j':
		opt_realtime_playing = (opt_realtime_playing) ? 0 : 1;
		break;
	case 'K':
		return parse_opt_K(optarg);
	case 'k':
		return parse_opt_k(optarg);
	case 'L':
		return parse_opt_L(optarg);
	case 'M':
		return parse_opt_M(optarg);
	case 'm':
		return parse_opt_m(optarg);
	case 'N':
		return parse_opt_N(optarg);
	case 'O':
		return parse_opt_O(optarg);
	case 'o':
		return parse_opt_o(optarg);
	case 'P':
		return parse_opt_P(optarg);
	case 'p':
		if (*optarg != 'a')
			err += parse_opt_p(optarg);
		if (strchr(optarg, 'a'))
			auto_reduce_polyphony = (auto_reduce_polyphony) ? 0 : 1;
		return err;
	case 'Q':
		return parse_opt_Q(optarg);
	case 'q':
		return parse_opt_q(optarg);
	case 'R':
		return parse_opt_R(optarg);
	case 'S':
		return parse_opt_S(optarg);
	case 's':
		return parse_opt_s(optarg);
	case 'T':
		return parse_opt_T(optarg);
	case 't':
		return parse_opt_t(optarg);
	case 'U':
		free_instruments_afterwards = 1;
		break;
	case 'V':
		return parse_opt_volume_curve(optarg);
	case 'v':
		return parse_opt_v(optarg);
#ifdef __W32__
	case 'w':
		return parse_opt_w(optarg);
#endif
	case 'x':
		return parse_opt_x(optarg);
	case 'Z':
		if (strncmp(optarg, "pure", 4))
			return parse_opt_Z(optarg);
		else
			return parse_opt_Z1(optarg + 4);
	default:
		return 1;
	}
