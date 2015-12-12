#ifdef WLAN_NS_OFFLOAD
if(SIR_IPV6_NS_OFFLOAD == pRequest->offloadType)
        {
            status = pmcSetNSOffload( hHal, pRequest ,pSession->connectedProfile.bssid);
        }
        else
#endif //WLAN_NS_OFFLOAD
        {
            status = pmcSetHostOffload (hHal, pRequest, pSession->connectedProfile.bssid);
        }
