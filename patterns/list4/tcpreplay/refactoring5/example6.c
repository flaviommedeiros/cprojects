#ifdef HAVE_NETMAP
if (sendpacket_type == SP_TYPE_NETMAP)
            sp = (sendpacket_t*)sendpacket_open_netmap(device, errbuf, arg);
        else
#endif
#if defined HAVE_PF_PACKET
            sp = sendpacket_open_pf(device, errbuf);
