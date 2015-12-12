#ifdef RB_IPV6
if(fam == AF_INET6) {

            for (b = 128; b >= 0; b -= 16) {
                for (arec = atable[hash_ipv6(addr, b)]; arec; arec = arec->next)
                    if(arec->type == (type & ~0x1) &&
                       arec->masktype == HM_IPV6 &&
                       comp_with_mask_sock(addr, (struct sockaddr *)&arec->Mask.ipa.addr,
                                           arec->Mask.ipa.bits) &&
                       (type & 0x1 || match(arec-> username, username)) &&
                       (type != CONF_CLIENT || !arec->auth_user ||
                        (auth_user && match(arec->auth_user, auth_user))) &&
                       arec->precedence > hprecv) {
                        hprecv = arec->precedence;
                        hprec = arec->aconf;
                    }
            }
        } else
#endif
            if(fam == AF_INET) {
                for (b = 32; b >= 0; b -= 8) {
                    for (arec = atable[hash_ipv4(addr, b)]; arec; arec = arec->next)
                        if(arec->type == (type & ~0x1) &&
                           arec->masktype == HM_IPV4 &&
                           comp_with_mask_sock(addr, (struct sockaddr *)&arec->Mask.ipa.addr,
                                               arec->Mask.ipa.bits) &&
                           (type & 0x1 || match(arec->username, username)) &&
                           (type != CONF_CLIENT || !arec->auth_user ||
                            (auth_user && match(arec->auth_user, auth_user))) &&
                           arec->precedence > hprecv) {
                            hprecv = arec->precedence;
                            hprec = arec->aconf;
                        }
                }
            }
