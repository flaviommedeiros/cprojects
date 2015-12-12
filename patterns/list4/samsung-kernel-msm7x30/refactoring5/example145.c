#ifndef GEN6_ONWARDS
if(pMac->hal.pHalDxe){
#ifdef RTL8652
        extern void * rtlglue_is_data_scratchpad_memory(void *);
        if(rtlglue_is_data_scratchpad_memory(pMac->hal.pHalDxe))
            ;
        else
#endif
            palFreeMemory(pMac, pMac->hal.pHalDxe);
    }
