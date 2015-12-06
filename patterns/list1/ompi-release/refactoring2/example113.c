#if defined(VT_CUPTI_ACTIVITY)
if(vt_cupti_events_enabled || (vt_gpu_sync_level > 2 &&
     (vt_gpu_config & VT_GPU_TRACE_SYNC) == VT_GPU_TRACE_SYNC))
#endif
    {
      if(!vt_cupticb_trace_driverAPI)
        time = vt_pform_wtime();
      
      /****************** synchronous CUDA memory copies **********************/
      switch(cbid){
        case CUPTI_DRIVER_TRACE_CBID_cuMemcpy: {
          cuMemcpy_params *params = 
                (cuMemcpy_params *)cbInfo->functionParams;
          
          vt_cupti_handle_memcpyDefault(cbInfo, params->src, params->dst, 
                                        params->ByteCount, time);

          return;
        }
        
        case CUPTI_DRIVER_TRACE_CBID_cuMemcpy2D_v2: {
          cuMemcpy2D_v2_params *params = 
                (cuMemcpy2D_v2_params *)cbInfo->functionParams;
          
          size_t bytes = params->pCopy->WidthInBytes * params->pCopy->Height;
          
          vt_cupti_handle_memcpyDefault(cbInfo, params->pCopy->srcDevice,
                                        params->pCopy->dstDevice, time, bytes);
          
          return;
        }
        
        case CUPTI_DRIVER_TRACE_CBID_cuMemcpy3D_v2: {
          cuMemcpy3D_v2_params *params = 
                (cuMemcpy3D_v2_params *)cbInfo->functionParams;
          
          size_t bytes = params->pCopy->WidthInBytes * params->pCopy->Height
                       * params->pCopy->Depth;
          
          vt_cupti_handle_memcpyDefault(cbInfo, params->pCopy->srcDevice,
                                        params->pCopy->dstDevice, time, bytes);
          
          return;
        }
        
        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyPeer: {
          cuMemcpyPeer_params *params = 
                (cuMemcpyPeer_params *)cbInfo->functionParams;
          
          size_t bytes = params->ByteCount;
          
          vt_cupticb_handle_memcpyP2P(cbInfo, 
                                      params->srcContext, params->dstContext,
                                      bytes, time);
          
          return;
        }
        
        case CUPTI_DRIVER_TRACE_CBID_cuMemcpy3DPeer: {
          cuMemcpy3DPeer_params *params = 
                (cuMemcpy3DPeer_params *)cbInfo->functionParams;
          
          size_t bytes = params->pCopy->WidthInBytes 
                       * params->pCopy->Depth * params->pCopy->Height;
          
          vt_cupticb_handle_memcpyP2P(cbInfo, params->pCopy->srcContext, 
                                      params->pCopy->dstContext,
                                      bytes, time);
          
          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyHtoD: {
          cuMemcpyHtoD_params *params = 
                (cuMemcpyHtoD_params *)cbInfo->functionParams;

          vt_cupticb_handle_memcpy(cbInfo, cudaMemcpyHostToDevice, 
                                   params->ByteCount, time);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyHtoD_v2: {
          cuMemcpyHtoD_v2_params *params = 
                (cuMemcpyHtoD_v2_params *)cbInfo->functionParams;

          vt_cupticb_handle_memcpy(cbInfo, cudaMemcpyHostToDevice, 
                                   params->ByteCount, time);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyDtoH: {
          cuMemcpyDtoH_params *params = 
                (cuMemcpyDtoH_params *)cbInfo->functionParams;

          vt_cupticb_handle_memcpy(cbInfo, cudaMemcpyDeviceToHost, 
                                   params->ByteCount, time);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyDtoH_v2: {
          cuMemcpyDtoH_v2_params *params = 
                (cuMemcpyDtoH_v2_params *)cbInfo->functionParams;

          vt_cupticb_handle_memcpy(cbInfo, cudaMemcpyDeviceToHost, 
                                   params->ByteCount, time);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyDtoD: {
          cuMemcpyDtoD_params *params = 
                (cuMemcpyDtoD_params *)cbInfo->functionParams;

          vt_cupticb_handle_memcpy(cbInfo, cudaMemcpyDeviceToDevice, 
                                   params->ByteCount, time);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyDtoD_v2: {
          cuMemcpyDtoD_v2_params *params = 
                (cuMemcpyDtoD_v2_params *)cbInfo->functionParams;

          vt_cupticb_handle_memcpy(cbInfo, cudaMemcpyDeviceToDevice, 
                                   params->ByteCount, time);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyHtoA: {
          cuMemcpyHtoA_params *params = 
                (cuMemcpyHtoA_params *)cbInfo->functionParams;

          vt_cupticb_handle_memcpy(cbInfo, cudaMemcpyHostToDevice, 
                                   params->ByteCount, time);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyHtoA_v2: {
          cuMemcpyHtoA_v2_params *params = 
                (cuMemcpyHtoA_v2_params *)cbInfo->functionParams;

          vt_cupticb_handle_memcpy(cbInfo, cudaMemcpyHostToDevice, 
                                   params->ByteCount, time);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyAtoH: {
          cuMemcpyAtoH_params *params = 
                (cuMemcpyAtoH_params *)cbInfo->functionParams;

          vt_cupticb_handle_memcpy(cbInfo, cudaMemcpyDeviceToHost, 
                                   params->ByteCount, time);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyAtoH_v2: {
          cuMemcpyAtoH_v2_params *params = 
                (cuMemcpyAtoH_v2_params *)cbInfo->functionParams;

          vt_cupticb_handle_memcpy(cbInfo, cudaMemcpyDeviceToHost, 
                                   params->ByteCount, time);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyAtoA: {
          cuMemcpyAtoA_params *params = 
                (cuMemcpyAtoA_params *)cbInfo->functionParams;

          vt_cupticb_handle_memcpy(cbInfo, cudaMemcpyDeviceToDevice, 
                                   params->ByteCount, time);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuMemcpyAtoA_v2: {
          cuMemcpyAtoA_v2_params *params = 
                (cuMemcpyAtoA_v2_params *)cbInfo->functionParams;

          vt_cupticb_handle_memcpy(cbInfo, cudaMemcpyDeviceToDevice, 
                                   params->ByteCount, time);

          return;
        }

        default: break;
      } /* switch(cbid) */
    }
