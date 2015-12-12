#ifdef MT
if (check_ports(peer, t))
#else
            if (check_ports(peer))
#endif
                loops = threshold;
