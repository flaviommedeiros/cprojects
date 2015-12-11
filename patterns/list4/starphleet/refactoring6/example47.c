if (rn->naddrs == (u_short) -1
#if (NGX_HAVE_INET6)
            || rn->naddrs6 == (u_short) -1
#endif
            )
        {
            goto next;
        }
