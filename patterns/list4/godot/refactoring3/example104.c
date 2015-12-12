switch(request)
   {
   case SPEEX_SET_LOW_MODE:
   case SPEEX_SET_MODE:
      st->submodeID = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_GET_LOW_MODE:
   case SPEEX_GET_MODE:
      (*(spx_int32_t*)ptr) = st->submodeID;
      break;
   case SPEEX_SET_ENH:
      st->lpc_enh_enabled = *((spx_int32_t*)ptr);
      break;
   case SPEEX_GET_ENH:
      *((spx_int32_t*)ptr) = st->lpc_enh_enabled;
      break;
   case SPEEX_GET_FRAME_SIZE:
      (*(spx_int32_t*)ptr) = st->frameSize;
      break;
   case SPEEX_GET_BITRATE:
      if (st->submodes[st->submodeID])
         (*(spx_int32_t*)ptr) = st->sampling_rate*SUBMODE(bits_per_frame)/st->frameSize;
      else
         (*(spx_int32_t*)ptr) = st->sampling_rate*(NB_SUBMODE_BITS+1)/st->frameSize;
      break;
   case SPEEX_SET_SAMPLING_RATE:
      st->sampling_rate = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_GET_SAMPLING_RATE:
      (*(spx_int32_t*)ptr)=st->sampling_rate;
      break;
   case SPEEX_SET_HANDLER:
      {
         SpeexCallback *c = (SpeexCallback*)ptr;
         st->speex_callbacks[c->callback_id].func=c->func;
         st->speex_callbacks[c->callback_id].data=c->data;
         st->speex_callbacks[c->callback_id].callback_id=c->callback_id;
      }
      break;
   case SPEEX_SET_USER_HANDLER:
      {
         SpeexCallback *c = (SpeexCallback*)ptr;
         st->user_callback.func=c->func;
         st->user_callback.data=c->data;
         st->user_callback.callback_id=c->callback_id;
      }
      break;
   case SPEEX_RESET_STATE:
      {
         int i;
         for (i=0;i<st->lpcSize;i++)
            st->mem_sp[i]=0;
         for (i=0;i<st->frameSize + st->max_pitch + 1;i++)
            st->excBuf[i]=0;
      }
      break;
   case SPEEX_SET_SUBMODE_ENCODING:
      st->encode_submode = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_GET_SUBMODE_ENCODING:
      (*(spx_int32_t*)ptr) = st->encode_submode;
      break;
   case SPEEX_GET_LOOKAHEAD:
      (*(spx_int32_t*)ptr)=st->subframeSize;
      break;
   case SPEEX_SET_HIGHPASS:
      st->highpass_enabled = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_GET_HIGHPASS:
      (*(spx_int32_t*)ptr) = st->highpass_enabled;
      break;
      /* FIXME: Convert to fixed-point and re-enable even when float API is disabled */
#ifndef DISABLE_FLOAT_API
   case SPEEX_GET_ACTIVITY:
   {
      float ret;
      ret = log(st->level/st->min_level)/log(st->max_level/st->min_level);
      if (ret>1)
         ret = 1;
      /* Done in a strange way to catch NaNs as well */
      if (!(ret > 0))
         ret = 0;
      /*printf ("%f %f %f %f\n", st->level, st->min_level, st->max_level, ret);*/
      (*(spx_int32_t*)ptr) = (int)(100*ret);
   }
   break;
#endif
   case SPEEX_GET_PI_GAIN:
      {
         int i;
         spx_word32_t *g = (spx_word32_t*)ptr;
         for (i=0;i<st->nbSubframes;i++)
            g[i]=st->pi_gain[i];
      }
      break;
   case SPEEX_GET_EXC:
      {
         int i;
         for (i=0;i<st->nbSubframes;i++)
            ((spx_word16_t*)ptr)[i] = compute_rms16(st->exc+i*st->subframeSize, st->subframeSize);
      }
      break;
   case SPEEX_GET_DTX_STATUS:
      *((spx_int32_t*)ptr) = st->dtx_enabled;
      break;
   case SPEEX_SET_INNOVATION_SAVE:
      st->innov_save = (spx_word16_t*)ptr;
      break;
   case SPEEX_SET_WIDEBAND:
      st->isWideband = *((spx_int32_t*)ptr);
      break;
   case SPEEX_GET_STACK:
      *((char**)ptr) = st->stack;
      break;
   default:
      speex_warning_int("Unknown nb_ctl request: ", request);
      return -1;
   }
