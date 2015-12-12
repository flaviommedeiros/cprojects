#ifdef RB_IPV6
if(aftype == HM_IPV6)
            aftype = AF_INET6;
        else
#endif
            aftype = AF_INET;
