if(vt_gpu_trace_idle > 0 && vtCtx->strmList != NULL 
#if defined(VT_CUPTI_ACTIVITY)
     && vtCtx->activity != NULL && vtCtx->activity->gpuIdleOn == 1
#endif
    ){
    uint64_t idle_end = vt_pform_wtime();
    
    /*vt_warning("IDLEexit: %llu (%d)", idle_end, vtCtx->strmList->vtThrdID);*/
    vt_exit(vtCtx->strmList->vtThrdID, &idle_end);
  }
