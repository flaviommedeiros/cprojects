#if defined(VT_CUPTI_ACTIVITY)
if(vt_cupti_events_enabled || (vt_gpu_sync_level > 2 &&
     (vt_gpu_config & VT_GPU_TRACE_SYNC) == VT_GPU_TRACE_SYNC))
#endif
    {
      switch(cbid){
      /****************** synchronous CUDA memory copies **************************/
        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy_v3020: {
          cudaMemcpy_v3020_params *params = 
                (cudaMemcpy_v3020_params *)cbInfo->functionParams;

          VT_CUPTICB_MEMCPY_CUDART(cbInfo, params->kind, 
                                   params->src, params->dst,
                                   params->count, time);
          
          return;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2D_v3020: {
          cudaMemcpy2D_v3020_params *params = 
                  (cudaMemcpy2D_v3020_params *)cbInfo->functionParams;

          VT_CUPTICB_MEMCPY_CUDART(cbInfo, params->kind, 
                                   params->src, params->dst,
                                   (uint64_t)(params->height * params->width), 
                                   time);
          return;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToArray_v3020: {
          cudaMemcpyToArray_v3020_params *params = 
                  (cudaMemcpyToArray_v3020_params *)cbInfo->functionParams;

          VT_CUPTICB_MEMCPY_CUDART(cbInfo, params->kind, 
                                   params->src, params->dst,
                                   (uint64_t)params->count, time);
          return;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DToArray_v3020: {
          cudaMemcpy2DToArray_v3020_params *params = 
                  (cudaMemcpy2DToArray_v3020_params *)cbInfo->functionParams;

          VT_CUPTICB_MEMCPY_CUDART(cbInfo, params->kind, 
                                   params->src, params->dst,
                                   (uint64_t)(params->height * params->width), 
                                   time);
          return;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromArray_v3020: {
          cudaMemcpyFromArray_v3020_params *params = 
                  (cudaMemcpyFromArray_v3020_params *)cbInfo->functionParams;

          VT_CUPTICB_MEMCPY_CUDART(cbInfo, params->kind, 
                                   params->src, params->dst,
                                   (uint64_t)params->count, time);
          return;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DFromArray_v3020: {
          cudaMemcpy2DFromArray_v3020_params *params = 
                  (cudaMemcpy2DFromArray_v3020_params *)cbInfo->functionParams;

          VT_CUPTICB_MEMCPY_CUDART(cbInfo, params->kind, 
                                   params->src, params->dst,
                                   (uint64_t)(params->height * params->width), 
                                   time);
          return;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyArrayToArray_v3020: {
          cudaMemcpyArrayToArray_v3020_params *params = 
                  (cudaMemcpyArrayToArray_v3020_params *)cbInfo->functionParams;

          VT_CUPTICB_MEMCPY_CUDART(cbInfo, params->kind, 
                                   params->src, params->dst,
                                   (uint64_t)params->count, time);
          return;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DArrayToArray_v3020: {
          cudaMemcpy2DArrayToArray_v3020_params *params = 
                  (cudaMemcpy2DArrayToArray_v3020_params *)cbInfo->functionParams;

          VT_CUPTICB_MEMCPY_CUDART(cbInfo, params->kind, 
                                   params->src, params->dst,
                                   (uint64_t)(params->height * params->width), 
                                   time);
          return;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToSymbol_v3020: {
          cudaMemcpyToSymbol_v3020_params *params = 
                  (cudaMemcpyToSymbol_v3020_params *)cbInfo->functionParams;

          VT_CUPTICB_MEMCPY_CUDART(cbInfo, params->kind, 
                                   params->src, params->symbol,
                                   (uint64_t)params->count, time);
          return;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromSymbol_v3020: {
          cudaMemcpyFromSymbol_v3020_params *params = 
                  (cudaMemcpyFromSymbol_v3020_params *)cbInfo->functionParams;

          VT_CUPTICB_MEMCPY_CUDART(cbInfo, params->kind, 
                                   params->symbol, params->dst,
                                   (uint64_t)params->count, time);
          return;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3D_v3020: {
          cudaMemcpy3D_v3020_params *params = 
                  (cudaMemcpy3D_v3020_params *)cbInfo->functionParams;

          VT_CUPTICB_MEMCPY_CUDART(cbInfo, params->p->kind, 
                                   params->p->srcArray, params->p->dstArray,
                 (uint64_t)(params->p->extent.height * params->p->extent.width * 
                            params->p->extent.depth), 
                                   time);
          return;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyPeer_v4000: {
          cudaMemcpyPeer_v4000_params *params = 
                (cudaMemcpyPeer_v4000_params *)cbInfo->functionParams;

          CUcontext cuSrcCtx;
          CUcontext cuDstCtx;
          int cudaCurrDev = 0;
          
          DISABLE_CUDART_CALLBACKS();
          DISABLE_CUDRV_CALLBACKS();
          
          /* get the currently active device */
          cudaGetDevice(&cudaCurrDev);
          
          /* get the source and destination context */
          if(params->srcDevice == cudaCurrDev){
            cuSrcCtx = cbInfo->context;
            if(cudaSuccess != cudaSetDevice(params->dstDevice)){
              vt_warning("[CUPTI Callbacks] Could not set device in P2P mcyp!");
              return;
            }
            VT_CUDRV_CALL(cuCtxGetCurrent(&cuDstCtx), NULL);
          }else if(params->dstDevice == cudaCurrDev){
            cuDstCtx = cbInfo->context;
            if(cudaSuccess != cudaSetDevice(params->srcDevice)){
              vt_warning("[CUPTI Callbacks] Could not set device in P2P mcyp!");
              return;
            }
            VT_CUDRV_CALL(cuCtxGetCurrent(&cuSrcCtx), NULL);
          }else{
            vt_warning("[CUPTI Callbacks] Could not identify P2P memcpy!");
            return;
          }
          
          /* reset the original active device */
          if(cudaSuccess != cudaSetDevice(cudaCurrDev)){
            vt_error_msg("[CUPTI Callbacks] Could not reset device in P2P mcyp!");
          }
          
          ENABLE_CUDART_CALLBACKS();
          ENABLE_CUDRV_CALLBACKS();
          
          vt_cupticb_handle_memcpyP2P(cbInfo, cuSrcCtx, cuDstCtx, 
                                      (uint64_t)params->count, time);
          
          return;
        }

        case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DPeer_v4000: {
          cudaMemcpy3DPeer_v4000_params *params = 
                  (cudaMemcpy3DPeer_v4000_params *)cbInfo->functionParams;
          
          CUcontext cuSrcCtx;
          CUcontext cuDstCtx;
          int cudaCurrDev = 0;
          
          DISABLE_CUDART_CALLBACKS();
          DISABLE_CUDRV_CALLBACKS();
          
          /* get the currently active device */
          cudaGetDevice(&cudaCurrDev);
          
          /* get the source and destination context */
          if(params->p->srcDevice == cudaCurrDev){
            cuSrcCtx = cbInfo->context;
            if(cudaSuccess != cudaSetDevice(params->p->dstDevice)){
              vt_warning("[CUPTI Callbacks] Could not set device in P2P mcyp!");
              return;
            }
            VT_CUDRV_CALL(cuCtxGetCurrent(&cuDstCtx), NULL);
          }else if(params->p->dstDevice == cudaCurrDev){
            cuDstCtx = cbInfo->context;
            if(cudaSuccess != cudaSetDevice(params->p->srcDevice)){
              vt_warning("[CUPTI Callbacks] Could not set device in P2P mcyp!");
              return;
            }
            VT_CUDRV_CALL(cuCtxGetCurrent(&cuSrcCtx), NULL);
          }else{
            vt_warning("[CUPTI Callbacks] Could not identify P2P memcpy 3D!");
            return;
          }
          
          /* reset the original active device */
          if(cudaSuccess != cudaSetDevice(cudaCurrDev)){
            vt_error_msg("[CUPTI Callbacks] Could not reset device in P2P mcyp!");
          }
          
          ENABLE_CUDART_CALLBACKS();
          ENABLE_CUDRV_CALLBACKS();

          vt_cupticb_handle_memcpyP2P(cbInfo, cuSrcCtx, cuDstCtx,
                    (uint64_t)(params->p->extent.height * params->p->extent.width * 
                               params->p->extent.depth), 
                                          time);
          return;
        }
        
        default: break;
      } /* switch(cbid) */
    }
