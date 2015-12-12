switch (what) {
    case SIOCGIFFLAGS:
        sp->if_flags = (ifr.ifr_flags << 16) | (0xffff & ifr.ifr_flags);
        dbgx(1, "SIOCGIFFLAGS flags are 0x%x", sp->if_flags);
        break;

#ifdef linux
    case SIOCETHTOOL:
        switch (subcmd) {
        case ETHTOOL_GGSO:
            sp->gso = eval.data;
            dbgx(1, "ioctl SIOCETHTOOL ETHTOOL_GGSO=%u", eval.data);
            break;

        case ETHTOOL_GTSO:
            sp->tso = eval.data;
            dbgx(1, "ioctl SIOCETHTOOL ETHTOOL_GTSO=%u", eval.data);
            break;

        case ETHTOOL_GRXCSUM:
            sp->rxcsum = eval.data;
            dbgx(1, "ioctl SIOCETHTOOL ETHTOOL_GRXCSUM=%u", eval.data);
            break;

        case ETHTOOL_GTXCSUM:
            sp->txcsum = eval.data;
            dbgx(1, "ioctl SIOCETHTOOL ETHTOOL_GTXCSUM=%u", eval.data);
            break;
        }
        break;
#endif

    }
