#ifdef WLAN_SOFTAP_FEATURE
if (pAssocReq->reassocRequest == 1)
        subType = LIM_REASSOC;
    else 
        subType = LIM_ASSOC;
