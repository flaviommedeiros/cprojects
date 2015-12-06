#ifndef SL_TINY_EXT
if (MAX_CONCURRENT_ACTIONS > g_pCB->ObjPool[CurrObjIndex].NextIndex)
        {
            g_pCB->FreePoolIdx = g_pCB->ObjPool[CurrObjIndex].NextIndex;
        }
        else
#endif           
        {
            /* No further free actions available */
            g_pCB->FreePoolIdx = MAX_CONCURRENT_ACTIONS;
        }
