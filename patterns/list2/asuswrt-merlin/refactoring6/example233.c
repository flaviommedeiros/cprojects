if(
#if FF_API_HURRY_UP
           (s->hurry_up == 1 && h->nal_ref_idc  == 0) ||
#endif
           (avctx->skip_frame >= AVDISCARD_NONREF && h->nal_ref_idc  == 0))
            continue;
