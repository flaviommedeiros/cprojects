#if defined(VT_CUPTI_ACTIVITY)
if(vt_cupti_events_enabled)
#endif
  {
    if(vt_gpu_trace_kernels){
      switch(cbid){
        /*case CUPTI_DRIVER_TRACE_CBID_cuLaunch: {

            vt_cupticb_handle_cuda_kernel(cbInfo, NULL);

          break;
        }*/

        case CUPTI_DRIVER_TRACE_CBID_cuLaunchGrid: {
          cuLaunchGrid_params *params = 
                               (cuLaunchGrid_params *)cbInfo->functionParams;

          uint64_t blocks = params->grid_width;

          if(params->grid_height != 0) 
            blocks *= params->grid_height;

          vt_cupticb_handle_cuda_kernel(cbInfo, NULL, blocks);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuLaunchGridAsync: {
          cuLaunchGridAsync_params *params = 
                               (cuLaunchGridAsync_params *)cbInfo->functionParams;

          uint64_t blocks = params->grid_width;

          if(params->grid_height != 0) 
            blocks *= params->grid_height;

          vt_cupticb_handle_cuda_kernel(cbInfo, params->hStream, blocks);

          return;
        }

        case CUPTI_DRIVER_TRACE_CBID_cuLaunchKernel: {
          cuLaunchKernel_params *params = 
                                  (cuLaunchKernel_params *)cbInfo->functionParams;

          uint64_t blocks = params->gridDimX;

          if(params->gridDimY != 0) 
            blocks *= params->gridDimY;

          if(params->gridDimZ != 0) 
            blocks *= params->gridDimZ;

          vt_cupticb_handle_cuda_kernel(cbInfo, params->hStream, blocks);

          return;
        }

        default: break;
      }
    }/* vt_gpu_trace_kernels */
  }
