#ifdef RB_IPV6
if(t == HM_IPV6)
                t = AF_INET6;
            else
#endif
                t = AF_INET;
