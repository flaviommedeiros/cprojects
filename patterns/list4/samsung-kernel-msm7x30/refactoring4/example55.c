#if(defined(ANI_PRODUCT_TYPE_AP) || defined(ANI_PRODUCT_TYPE_AP_SDK))
if ((psessionEntry->limSystemRole == eLIM_AP_ROLE &&
        (! psessionEntry->gLimEdcaParamsBC[upToAc(tsinfo->traffic.userPrio)].aci.acm)) ||
        (psessionEntry->limSystemRole != eLIM_AP_ROLE &&
        (! psessionEntry->gLimEdcaParams[upToAc(tsinfo->traffic.userPrio)].aci.acm)))
#else
        if ((upToAc(tsinfo->traffic.userPrio) >= MAX_NUM_AC) || (! psessionEntry->gLimEdcaParams[upToAc(tsinfo->traffic.userPrio)].aci.acm))
#endif
        {
            limLog(pMac, LOGW, FL("DelTs with UP %d has no AC - ignoring request\n"),
                   tsinfo->traffic.userPrio);
            return;
        }
