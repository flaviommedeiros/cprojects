void
ts_print(netdissect_options *ndo,
         register const struct timeval *tvp)
{
	register int s;
	struct tm *tm;
	time_t Time;
	char buf[TS_BUF_SIZE];
	static struct timeval tv_ref;
	struct timeval tv_result;
	int negative_offset;
	int nano_prec;

	switch (ndo->ndo_tflag) {

	case 0: /* Default */
		s = (tvp->tv_sec + thiszone) % 86400;
		ND_PRINT((ndo, "%s ", ts_format(ndo, s, tvp->tv_usec, buf)));
		break;

	case 1: /* No time stamp */
		break;

	case 2: /* Unix timeval style */
		ND_PRINT((ndo, "%s ", ts_unix_format(ndo,
			  tvp->tv_sec, tvp->tv_usec, buf)));
		break;

	case 3: /* Microseconds/nanoseconds since previous packet */
        case 5: /* Microseconds/nanoseconds since first packet */
#ifdef HAVE_PCAP_SET_TSTAMP_PRECISION
		switch (ndo->ndo_tstamp_precision) {
		case PCAP_TSTAMP_PRECISION_MICRO:
			nano_prec = 0;
			break;
		case PCAP_TSTAMP_PRECISION_NANO:
			nano_prec = 1;
			break;
		default:
			nano_prec = 0;
			break;
		}
#else
		nano_prec = 0;
#endif
		if (!(netdissect_timevalisset(&tv_ref)))
			tv_ref = *tvp; /* set timestamp for first packet */

		negative_offset = netdissect_timevalcmp(tvp, &tv_ref, <);
		if (negative_offset)
			netdissect_timevalsub(&tv_ref, tvp, &tv_result, nano_prec);
		else
			netdissect_timevalsub(tvp, &tv_ref, &tv_result, nano_prec);

		ND_PRINT((ndo, (negative_offset ? "-" : " ")));

		ND_PRINT((ndo, "%s ", ts_format(ndo,
			  tv_result.tv_sec, tv_result.tv_usec, buf)));

                if (ndo->ndo_tflag == 3)
			tv_ref = *tvp; /* set timestamp for previous packet */
		break;

	case 4: /* Default + Date */
		s = (tvp->tv_sec + thiszone) % 86400;
		Time = (tvp->tv_sec + thiszone) - s;
		tm = gmtime (&Time);
		if (!tm)
			ND_PRINT((ndo, "Date fail  "));
		else
			ND_PRINT((ndo, "%04d-%02d-%02d %s ",
                               tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
                               ts_format(ndo, s, tvp->tv_usec, buf)));
		break;
	}
}
