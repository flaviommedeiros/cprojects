if ( ( pProc->inuse ) 
#if !(NOGARBAGE)
	   && ( IsValidProcessEntry( pProc->proc_id, pProc->reg_time))
#endif
	  ) {
       /* Someone's still using us...  Log it */
       OkToExit = FALSE;
       #ifdef DEV
         WarnLog("Process %d is still registered", pProc->proc_id);
       #endif
     }
