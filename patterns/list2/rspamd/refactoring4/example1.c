#ifdef RSPAM_UNIXSOCKET
if (connect (sock, (struct sockaddr *) &ssun, sizeof (struct sockaddr_un)) < 0)
#else
        if (connect (sock, (struct sockaddr *) &ssin, sizeof (struct sockaddr_in)) < 0)
#endif
        {
            if (ccnt < MAX_FAILS_C)
                usleep (1000);
            else
            {
                close (sock);
#ifdef RSPAM_UNIXSOCKET
                log_write (0, LOG_MAIN, "rspam-exim: socket connect to %s failed", (char *)socket_name);
#else
                log_write (0, LOG_MAIN, "rspam-exim: socket connect to %s:%u failed", daemonIP, daemonPort);
#endif
		return REJECT_ON_ERROR ? LOCAL_SCAN_TEMPREJECT:LOCAL_SCAN_ACCEPT;
            }
        }
        else
            break;
