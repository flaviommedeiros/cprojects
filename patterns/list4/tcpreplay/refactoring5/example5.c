#ifdef HAVE_QUICK_TX
if (sendpacket_type == SP_TYPE_QUICK_TX)
            sp = (sendpacket_t*)sendpacket_open_quick_tx(device, errbuf);
        else
#endif
#ifdef HAVE_NETMAP
        if (sendpacket_type == SP_TYPE_NETMAP)
            sp = (sendpacket_t*)sendpacket_open_netmap(device, errbuf, arg);
        else
#endif
#if defined HAVE_PF_PACKET
            sp = sendpacket_open_pf(device, errbuf);
