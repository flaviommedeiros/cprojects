#ifdef HAVE_RAW_OPTIONS
if (lsrr > 0) {
            register u_char *optlist;

            optlist = outp;
            outp += optlen;

            /*
             * final hop 
             */
            gwlist[lsrr] = to->sin_addr.s_addr;

            outip->ip_dst.s_addr = gwlist[0];

            /*
             * force 4 byte alignment 
             */
            optlist[0] = IPOPT_NOP;
            /*
             * loose source route option 
             */
            optlist[1] = IPOPT_LSRR;
            i = lsrr * sizeof(gwlist[0]);
            optlist[2] = i + 3;
            /*
             * Pointer to LSRR addresses 
             */
            optlist[3] = IPOPT_MINOFF;
            memcpy(optlist + 4, gwlist + 1, i);
        } else
#endif
            outip->ip_dst = to->sin_addr;
