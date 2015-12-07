if(hx->redundant_pic_count==0 && hx->intra_gb_ptr && hx->s.data_partitioning
               && s->current_picture_ptr
               && s->context_initialized
#if FF_API_HURRY_UP
               && s->hurry_up < 5
#endif
               && (avctx->skip_frame < AVDISCARD_NONREF || hx->nal_ref_idc)
               && (avctx->skip_frame < AVDISCARD_BIDIR  || hx->slice_type_nos!=AV_PICTURE_TYPE_B)
               && (avctx->skip_frame < AVDISCARD_NONKEY || hx->slice_type_nos==AV_PICTURE_TYPE_I)
               && avctx->skip_frame < AVDISCARD_ALL)
                context_count++;
