switch (FID(next)) {
		case FID_REG:
			if (gtp_frame2file_r(grs, &data_size, next))
				return -1;
			break;
		case FID_MEM:
			if (gtp_frame2file_m(grs, &data_size, next))
				return -1;
			break;
		case FID_VAR:
			if (gtp_frame2file_v(grs, &data_size, next))
				return -1;
			break;
#ifdef GTP_FTRACE_RING_BUFFER
		case FID_HEAD:
			goto out;
			break;
#endif
		}
