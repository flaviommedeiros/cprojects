switch (accurate) {
#ifdef HAVE_SELECT
    case accurate_select:
        select_sleep(nap_this_time);
        break;
#endif

#ifdef HAVE_IOPERM
    case accurate_ioport:
        /* TODO investigate - I don't think this can ever get called */
        ioport_sleep(nap_this_time);
        break;
#endif

    case accurate_gtod:
        gettimeofday_sleep(nap_this_time);
        break;

    case accurate_nanosleep:
        nanosleep_sleep(nap_this_time);
        break;

    default:
        errx(-1, "Unknown timer mode %d", accurate);
    }
