switch (platform_type) {
#ifdef FTDI4222
        case MRAA_FTDI_FT4222:
            sub_plat = mraa_ftdi_ft4222();
            break;
#endif
        default:
            // this is not an error but more that we didn't find a USB platform extender we recognise
            syslog(LOG_DEBUG, "Unknown USB Platform Extender, currently not supported by MRAA");
    }
