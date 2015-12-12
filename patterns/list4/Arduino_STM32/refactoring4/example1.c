#if CFG_ROBIN_EN >0
if ((RunPrio == RdyPrio) && (yield || (OSCheckTime == OSTickCnt)))  
#else /* simple yield */  
    else if ((RunPrio == RdyPrio) && yield)  
#endif  
    {
        TCBNext        = pRdyTcb;   /* Yes,set TCBNext and reorder READY list */
        InsertToTCBRdyList(pCurTcb);
		RemoveFromTCBRdyList(pRdyTcb);
        pRdyTcb->state = TASK_RUNNING;
    }
    else
    {								    
        return;	
    }
