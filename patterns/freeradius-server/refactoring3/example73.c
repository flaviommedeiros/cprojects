switch (conf->stats.out) {
	default:
	case RS_STATS_OUT_STDIO_FANCY:
		update.head = NULL;
		update.body = rs_stats_print_fancy;
		break;

	case RS_STATS_OUT_STDIO_CSV:
		update.head = rs_stats_print_csv_header;
		update.body = rs_stats_print_csv;
		break;

#ifdef HAVE_COLLECTDC_H
	case RS_STATS_OUT_COLLECTD:
		update.head = NULL;
		update.body = NULL;
		break;
#endif
	}
