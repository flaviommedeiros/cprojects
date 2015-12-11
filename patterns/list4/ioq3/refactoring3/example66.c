switch (request)
   {
      case OPUS_SET_COMPLEXITY_REQUEST:
      {
         int value = va_arg(ap, opus_int32);
         if (value<0 || value>10)
            goto bad_arg;
         st->complexity = value;
      }
      break;
      case CELT_SET_START_BAND_REQUEST:
      {
         opus_int32 value = va_arg(ap, opus_int32);
         if (value<0 || value>=st->mode->nbEBands)
            goto bad_arg;
         st->start = value;
      }
      break;
      case CELT_SET_END_BAND_REQUEST:
      {
         opus_int32 value = va_arg(ap, opus_int32);
         if (value<1 || value>st->mode->nbEBands)
            goto bad_arg;
         st->end = value;
      }
      break;
      case CELT_SET_PREDICTION_REQUEST:
      {
         int value = va_arg(ap, opus_int32);
         if (value<0 || value>2)
            goto bad_arg;
         st->disable_pf = value<=1;
         st->force_intra = value==0;
      }
      break;
      case OPUS_SET_PACKET_LOSS_PERC_REQUEST:
      {
         int value = va_arg(ap, opus_int32);
         if (value<0 || value>100)
            goto bad_arg;
         st->loss_rate = value;
      }
      break;
      case OPUS_SET_VBR_CONSTRAINT_REQUEST:
      {
         opus_int32 value = va_arg(ap, opus_int32);
         st->constrained_vbr = value;
      }
      break;
      case OPUS_SET_VBR_REQUEST:
      {
         opus_int32 value = va_arg(ap, opus_int32);
         st->vbr = value;
      }
      break;
      case OPUS_SET_BITRATE_REQUEST:
      {
         opus_int32 value = va_arg(ap, opus_int32);
         if (value<=500 && value!=OPUS_BITRATE_MAX)
            goto bad_arg;
         value = IMIN(value, 260000*st->channels);
         st->bitrate = value;
      }
      break;
      case CELT_SET_CHANNELS_REQUEST:
      {
         opus_int32 value = va_arg(ap, opus_int32);
         if (value<1 || value>2)
            goto bad_arg;
         st->stream_channels = value;
      }
      break;
      case OPUS_SET_LSB_DEPTH_REQUEST:
      {
          opus_int32 value = va_arg(ap, opus_int32);
          if (value<8 || value>24)
             goto bad_arg;
          st->lsb_depth=value;
      }
      break;
      case OPUS_GET_LSB_DEPTH_REQUEST:
      {
          opus_int32 *value = va_arg(ap, opus_int32*);
          *value=st->lsb_depth;
      }
      break;
      case OPUS_SET_EXPERT_FRAME_DURATION_REQUEST:
      {
          opus_int32 value = va_arg(ap, opus_int32);
          st->variable_duration = value;
      }
      break;
      case OPUS_RESET_STATE:
      {
         int i;
         opus_val16 *oldBandE, *oldLogE, *oldLogE2;
         oldBandE = (opus_val16*)(st->in_mem+st->channels*(st->overlap+COMBFILTER_MAXPERIOD));
         oldLogE = oldBandE + st->channels*st->mode->nbEBands;
         oldLogE2 = oldLogE + st->channels*st->mode->nbEBands;
         OPUS_CLEAR((char*)&st->ENCODER_RESET_START,
               opus_custom_encoder_get_size(st->mode, st->channels)-
               ((char*)&st->ENCODER_RESET_START - (char*)st));
         for (i=0;i<st->channels*st->mode->nbEBands;i++)
            oldLogE[i]=oldLogE2[i]=-QCONST16(28.f,DB_SHIFT);
         st->vbr_offset = 0;
         st->delayedIntra = 1;
         st->spread_decision = SPREAD_NORMAL;
         st->tonal_average = 256;
         st->hf_average = 0;
         st->tapset_decision = 0;
      }
      break;
#ifdef CUSTOM_MODES
      case CELT_SET_INPUT_CLIPPING_REQUEST:
      {
         opus_int32 value = va_arg(ap, opus_int32);
         st->clip = value;
      }
      break;
#endif
      case CELT_SET_SIGNALLING_REQUEST:
      {
         opus_int32 value = va_arg(ap, opus_int32);
         st->signalling = value;
      }
      break;
      case CELT_SET_ANALYSIS_REQUEST:
      {
         AnalysisInfo *info = va_arg(ap, AnalysisInfo *);
         if (info)
            OPUS_COPY(&st->analysis, info, 1);
      }
      break;
      case CELT_GET_MODE_REQUEST:
      {
         const CELTMode ** value = va_arg(ap, const CELTMode**);
         if (value==0)
            goto bad_arg;
         *value=st->mode;
      }
      break;
      case OPUS_GET_FINAL_RANGE_REQUEST:
      {
         opus_uint32 * value = va_arg(ap, opus_uint32 *);
         if (value==0)
            goto bad_arg;
         *value=st->rng;
      }
      break;
      case OPUS_SET_LFE_REQUEST:
      {
          opus_int32 value = va_arg(ap, opus_int32);
          st->lfe = value;
      }
      break;
      case OPUS_SET_ENERGY_MASK_REQUEST:
      {
          opus_val16 *value = va_arg(ap, opus_val16*);
          st->energy_mask = value;
      }
      break;
      default:
         goto bad_request;
   }
