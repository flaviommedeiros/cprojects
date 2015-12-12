#ifdef RB_IPV6
if(masktype == HM_IPV6) {
        /* We have to do this, since we do not re-hash for every bit -A1kmm. */
        bits -= bits % 16;
        hv = hash_ipv6((struct sockaddr *)&addr, bits);
    } else
#endif
        if(masktype == HM_IPV4) {
            /* We have to do this, since we do not re-hash for every bit -A1kmm. */
            bits -= bits % 8;
            hv = hash_ipv4((struct sockaddr *)&addr, bits);
        } else
            hv = get_mask_hash(address);
