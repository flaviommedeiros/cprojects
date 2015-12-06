static void vt_cupticb_handle_cudart_mcpyAsync(const CUpti_CallbackData *cbInfo,
                                               enum cudaMemcpyKind kind,
                                               uint64_t bytes,
                                               cudaStream_t cuStrm)
{
  uint32_t strmID;
  uint32_t ptid;
  uint64_t time;
  
  VT_CHECK_THREAD;
  ptid = VT_MY_THREAD;

  if(cbInfo->callbackSite == CUPTI_API_ENTER){
    /* get the VampirTrace thread ID the kernel is running on */
    {
      vt_cupti_ctx_t *vtCtx = vt_cupti_getCreateCtx(cbInfo->context);
      vt_cupti_strm_t *vtStrm = NULL;
      uint32_t cuStrmID = VT_CUPTI_NO_STREAM_ID;
    
      if(vt_gpu_init_time < vt_start_time)
        vt_gpu_init_time = vt_start_time;

#if defined(VT_CUPTI_ACTIVITY)
      if(vtCtx->activity == NULL){
        VT_CUPTI_CALL(cuptiGetStreamId(cbInfo->context, cuStrm, &cuStrmID), 
                                       "cuptiGetStreamId");
      }else{
        cuStrmID = vtCtx->activity->defaultStrmID;
      }
#endif /* VT_CUPTI_ACTIVITY */

      vtStrm = vt_cupti_getCreateStream(vtCtx, cuStrm, cuStrmID);
      
      strmID = vtStrm->vtThrdID;

      /* save address into 64 Bit correlation value for exit callback */
      *cbInfo->correlationData = (uint64_t)vtStrm;
    }

    VT_CUPTI_LOCK();
    if(kind != cudaMemcpyDeviceToDevice) vt_gpu_prop[ptid] |= VTGPU_GPU_COMM;
    vt_gpu_prop[strmID] |= VTGPU_GPU_COMM;
    VT_CUPTI_UNLOCK();

    time = vt_pform_wtime();
    if(kind == cudaMemcpyHostToDevice){
      vt_mpi_rma_put(ptid, &time, VT_GPU_RANK_ID(strmID),
                     vt_gpu_commCID, 0, bytes);
    }else if(kind == cudaMemcpyDeviceToHost){
      vt_mpi_rma_get(ptid, &time, VT_GPU_RANK_ID(strmID),
                     vt_gpu_commCID, 0, bytes);
    }else if(kind == cudaMemcpyDeviceToDevice){
      vt_mpi_rma_get(strmID, &time, VT_GPU_RANK_ID(strmID),
                     vt_gpu_commCID, 0, bytes);
    }
  }

  if(cbInfo->callbackSite == CUPTI_API_EXIT){
    strmID = ((vt_cupti_strm_t *)(*cbInfo->correlationData))->vtThrdID;

    /* synchronize to get host waiting time */
    if(vt_gpu_sync_level > 0){
      time = vt_cupticb_synchronizeCtx(ptid);
    }else{
      time = vt_pform_wtime();
    }

    if(kind == cudaMemcpyDeviceToDevice){
      vt_mpi_rma_end(strmID, &time, vt_gpu_commCID, 0);
    }else if(kind != cudaMemcpyHostToHost){
      vt_mpi_rma_end(ptid, &time, vt_gpu_commCID, 0);
    }
  }
}
