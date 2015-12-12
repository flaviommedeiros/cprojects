#ifdef WLAN_SOFTAP_FEATURE
if ((psessionEntry->limSystemRole == eLIM_AP_ROLE ) &&
       psessionEntry->gLimNoShortSlotParams.numNonShortSlotSta> 0)
       {
          for (i=0; i<LIM_PROT_STA_CACHE_SIZE; i++)
          {
             if (psessionEntry->gLimNoShortSlotParams.staNoShortSlotCache[i].active)
             {
                if (palEqualMemory( pMac->hHdd, psessionEntry->gLimNoShortSlotParams.staNoShortSlotCache[i].addr,
                    pStaDs->staAddr, sizeof(tSirMacAddr)))
                    {
                        psessionEntry->gLimNoShortSlotParams.numNonShortSlotSta--;
                        psessionEntry->gLimNoShortSlotParams.staNoShortSlotCache[i].active = false;
                        break;
                    }
             }
          }
       }
       else
#endif
       {
           if (pMac->lim.gLimNoShortSlotParams.numNonShortSlotSta> 0)
           {
             for (i=0; i<LIM_PROT_STA_CACHE_SIZE; i++)
             {
               if (pMac->lim.gLimNoShortSlotParams.staNoShortSlotCache[i].active)
               {
                  if (palEqualMemory( pMac->hHdd, pMac->lim.gLimNoShortSlotParams.staNoShortSlotCache[i].addr,
                      pStaDs->staAddr, sizeof(tSirMacAddr)))
                  {
                      pMac->lim.gLimNoShortSlotParams.numNonShortSlotSta--;
                      pMac->lim.gLimNoShortSlotParams.staNoShortSlotCache[i].active = false;
                      break;
                  }
               }
             }
           }
         }
