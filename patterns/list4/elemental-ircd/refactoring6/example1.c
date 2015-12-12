if((aconf = find_address_conf(host, NULL, user_trunc, notildeuser_trunc,
                                  (type != HM_HOST) ? (struct sockaddr *)&ip : NULL,
                                  (type != HM_HOST) ? (
#ifdef RB_IPV6
                                      (type == HM_IPV6) ? AF_INET6 :
#endif
                                      AF_INET) : 0, NULL))) {
        static char buf[HOSTLEN+USERLEN+2];

        if(aconf->status & CONF_KILL) {
            get_printable_kline(source_p, aconf, &phost, &reason, &puser, &operreason);
            snprintf(buf, sizeof(buf), "%s@%s",
                        puser, phost);
            snprintf(reasonbuf, sizeof(reasonbuf), "%s%s%s", reason,
                        operreason ? "|" : "", operreason ? operreason : "");
            sendto_one(source_p, form_str(RPL_TESTLINE),
                       me.name, source_p->name,
                       (aconf->flags & CONF_FLAGS_TEMPORARY) ? 'k' : 'K',
                       (aconf->flags & CONF_FLAGS_TEMPORARY) ?
                       (long) ((aconf->hold - rb_current_time()) / 60) : 0L,
                       buf, reasonbuf);
            return 0;
        }
    }
