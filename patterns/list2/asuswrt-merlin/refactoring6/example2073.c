if ((ifrp->ifr_flags & IFF_UP)
#ifdef IFF_RUNNING
            && (ifrp->ifr_flags & IFF_RUNNING)
#endif                          /* IFF_RUNNING */
            && !(ifrp->ifr_flags & IFF_LOOPBACK)
            && addr != LOOPBACK) {
            /*
             * I *really* don't understand why this is necessary.  Perhaps for
             * some broken platform?  Leave it for now.  JBPN  
             */
#ifdef SYS_IOCTL_H_HAS_SIOCGIFADDR
            if (ioctl(sd, SIOCGIFADDR, (char *) ifrp) < 0) {
                continue;
            }
            addr =
                ((struct sockaddr_in *) &(ifrp->ifr_addr))->sin_addr.
                s_addr;
#endif
            free(buf);
            close(sd);
            return addr;
        }
