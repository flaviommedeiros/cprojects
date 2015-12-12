switch (what) {
    case SIOCSIFFLAGS:
        ifr.ifr_flags = sp->if_flags >> 16;
        ifr.ifr_flags = sp->if_flags & 0xffff;
        break;

#ifdef linux
    case SIOCETHTOOL:
        eval.cmd = subcmd;
        eval.data = sp->data;
        ifr.ifr_data = (caddr_t)&eval;
        dbgx(1, "ioctl SIOCETHTOOL subcmd=%d data=%u", subcmd, eval.data);
        break;
#endif
    }
