#if defined(VT_CUPTI_ACTIVITY)
if(vt_cupti_events_enabled)
#endif
  {
    if(vt_gpu_trace_kernels){
      switch(cbid){

        /************* the CUDA runtime kernel configure call ************/
        case CUPTI_RUNTIME_TRACE_CBID_cudaConfigureCall_v3020: {
          if(vt_cupti_events_enabled && vt_gpu_trace_kernels && 
             cbInfo->callbackSite == CUPTI_API_EXIT)
            vt_cupticb_handle_cudart_knconf(cbInfo);

          return;
        }

        /***** the CUDA runtime kernel launch ******/
        case CUPTI_RUNTIME_TRACE_CBID_cudaLaunch_v3020: {
          if(vt_cupti_events_enabled && vt_gpu_trace_kernels)
            vt_cupticb_handle_cuda_kernel(cbInfo, NULL, 0);

          return;
        }
        
        default: break;
      }
    }
    /****************************************************************************/
      
    if(vt_gpu_trace_mcpy){
      switch(cbid){
        /******************** asynchronous memory copies **************************/
        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyAsync_v3020: {
          cudaMemcpyAsync_v3020_params *params = 
                (cudaMemcpyAsync_v3020_params *)cbInfo->functionParams;

          vt_cupticb_handle_cudart_mcpyAsync(cbInfo, params->kind, 
                                             (uint64_t)params->count, 
                                             params->stream);
          break;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToArrayAsync_v3020: {
          cudaMemcpyToArrayAsync_v3020_params *params = 
                  (cudaMemcpyToArrayAsync_v3020_params *)cbInfo->functionParams;

          vt_cupticb_handle_cudart_mcpyAsync(cbInfo, params->kind, 
                                             (uint64_t)params->count, 
                                             params->stream);
          break;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromArrayAsync_v3020: {
          cudaMemcpyFromArrayAsync_v3020_params *params = 
                  (cudaMemcpyFromArrayAsync_v3020_params *)cbInfo->functionParams;

          vt_cupticb_handle_cudart_mcpyAsync(cbInfo, params->kind, 
                                          (uint64_t)params->count, 
                                          params->stream);
          break;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DAsync_v3020: {
          cudaMemcpy2DAsync_v3020_params *params = 
                  (cudaMemcpy2DAsync_v3020_params *)cbInfo->functionParams;

          vt_cupticb_handle_cudart_mcpyAsync(cbInfo, params->kind, 
                                          (uint64_t)(params->height * params->width), 
                                          params->stream);
          break;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DToArrayAsync_v3020: {
          cudaMemcpy2DToArrayAsync_v3020_params *params = 
                  (cudaMemcpy2DToArrayAsync_v3020_params *)cbInfo->functionParams;

          vt_cupticb_handle_cudart_mcpyAsync(cbInfo, params->kind, 
                                          (uint64_t)(params->height * params->width), 
                                          params->stream);
          break;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DFromArrayAsync_v3020: {
          cudaMemcpy2DFromArrayAsync_v3020_params *params = 
                  (cudaMemcpy2DFromArrayAsync_v3020_params *)cbInfo->functionParams;

          vt_cupticb_handle_cudart_mcpyAsync(cbInfo, params->kind, 
                                          (uint64_t)(params->height * params->width), 
                                          params->stream);
          break;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToSymbolAsync_v3020: {
          cudaMemcpyToSymbolAsync_v3020_params *params = 
                  (cudaMemcpyToSymbolAsync_v3020_params *)cbInfo->functionParams;

          vt_cupticb_handle_cudart_mcpyAsync(cbInfo, params->kind, 
                                          (uint64_t)params->count, 
                                          params->stream);
          break;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromSymbolAsync_v3020: {
          cudaMemcpyFromSymbolAsync_v3020_params *params = 
                  (cudaMemcpyFromSymbolAsync_v3020_params *)cbInfo->functionParams;

          vt_cupticb_handle_cudart_mcpyAsync(cbInfo, params->kind, 
                                          (uint64_t)params->count, 
                                          params->stream);
          break;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DAsync_v3020: {
          cudaMemcpy3DAsync_v3020_params *params = 
                  (cudaMemcpy3DAsync_v3020_params *)cbInfo->functionParams;

          vt_cupticb_handle_cudart_mcpyAsync(cbInfo, params->p->kind, 
                    (uint64_t)(params->p->extent.height * params->p->extent.width * 
                               params->p->extent.depth), 
                                          params->stream);
          break;
        }
        /*
        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyPeerAsync_v4000: {
          cudaMemcpyPeerAsync_v4000_params *params = 
                (cudaMemcpyPeerAsync_v4000_params *)cbInfo->functionParams;

          vt_cupticb_handle_cudart_mcpyAsync(cbInfo, cudaMemcpyDeviceToDevice, 
                                          (uint64_t)params->count, 
                                          params->stream);
          break;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DPeerAsync_v4000: {
          cudaMemcpy3DPeerAsync_v4000_params *params = 
                  (cudaMemcpy3DPeerAsync_v4000_params *)cbInfo->functionParams;

          vt_cupticb_handle_cudart_mcpyAsync(cbInfo, cudaMemcpyDeviceToDevice, 
                    (uint64_t)(params->p->extent.height * params->p->extent.width * 
                               params->p->extent.depth), 
                                          params->stream);
          break;
        }*/
        /**************************************************************************/

        default: break;
      } /* switch(cbid) */
    } /* if(vt_gpu_trace_memcpy) */
  }
