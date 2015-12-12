#ifdef WLAN_SOFTAP_FEATURE
if (pAssocReq->addIEPresent && pAssocReq->addIE.length )
            wpsIe = limGetWscIEPtr(pMac, pAssocReq->addIE.addIEdata, pAssocReq->addIE.length);
