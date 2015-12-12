if (!avctx->hwaccel
#if FF_API_CAP_VDPAU
            && !(avctx->codec->capabilities&AV_CODEC_CAP_HWACCEL_VDPAU)
#endif
            ) {
            for(i=0; i<avctx->height; i++)
                memset(s->last_picture_ptr->f->data[0] + s->last_picture_ptr->f->linesize[0]*i,
                       0x80, avctx->width);
            if (s->last_picture_ptr->f->data[2]) {
                for(i=0; i<FF_CEIL_RSHIFT(avctx->height, v_chroma_shift); i++) {
                    memset(s->last_picture_ptr->f->data[1] + s->last_picture_ptr->f->linesize[1]*i,
                        0x80, FF_CEIL_RSHIFT(avctx->width, h_chroma_shift));
                    memset(s->last_picture_ptr->f->data[2] + s->last_picture_ptr->f->linesize[2]*i,
                        0x80, FF_CEIL_RSHIFT(avctx->width, h_chroma_shift));
                }
            }

            if(s->codec_id == AV_CODEC_ID_FLV1 || s->codec_id == AV_CODEC_ID_H263){
                for(i=0; i<avctx->height; i++)
                memset(s->last_picture_ptr->f->data[0] + s->last_picture_ptr->f->linesize[0]*i, 16, avctx->width);
            }
        }
