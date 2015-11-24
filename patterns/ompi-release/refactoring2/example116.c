#if defined(VT_CUPTI_ACTIVITY)
if(!vt_cupti_events_enabled)
# endif
  {
    /* synchronize context before 
       (assume that the given context is the current one) */
    if(!(vt_gpu_trace_kernels && vt_gpu_trace_mcpy) ||
       ((vt_gpu_trace_kernels || vt_gpu_trace_mcpy) && 
                                !vt_cupti_activity_isBufferEmpty(vtCtx->cuCtx)))
      vt_cupticb_synchronizeCtx(vtCtx->ptid);
  }
