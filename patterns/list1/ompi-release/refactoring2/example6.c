#if defined(VT_CUPTI_EVENTS)
if(!vt_cupti_events_enabled)
#endif
          {
            /* increment buffers */
            vtDev->evtbuf_pos++;
            vtDev->buf_pos += sizeof(VTCUDAKernel);
          }
