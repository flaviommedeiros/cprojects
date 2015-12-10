switch (c->fmt) {
        case ZMBV_FMT_8BPP:
            c->bpp = 8;
            decode_intra = zmbv_decode_intra;
            c->decode_xor = zmbv_decode_xor_8;
            avctx->pix_fmt = AV_PIX_FMT_PAL8;
            c->stride = c->width;
            break;
        case ZMBV_FMT_15BPP:
        case ZMBV_FMT_16BPP:
            c->bpp = 16;
            decode_intra = zmbv_decode_intra;
            c->decode_xor = zmbv_decode_xor_16;
            if (c->fmt == ZMBV_FMT_15BPP)
                avctx->pix_fmt = AV_PIX_FMT_RGB555LE;
            else
                avctx->pix_fmt = AV_PIX_FMT_RGB565LE;
            c->stride = c->width * 2;
            break;
#ifdef ZMBV_ENABLE_24BPP
        case ZMBV_FMT_24BPP:
            c->bpp = 24;
            decode_intra = zmbv_decode_intra;
            c->decode_xor = zmbv_decode_xor_24;
            avctx->pix_fmt = AV_PIX_FMT_RGB24;
            c->stride = c->width * 3;
            break;
#endif //ZMBV_ENABLE_24BPP
        case ZMBV_FMT_32BPP:
            c->bpp = 32;
            decode_intra = zmbv_decode_intra;
            c->decode_xor = zmbv_decode_xor_32;
            avctx->pix_fmt = AV_PIX_FMT_BGR0;
            c->stride = c->width * 4;
            break;
        default:
            c->decode_xor = NULL;
            avpriv_request_sample(avctx, "Format %i", c->fmt);
            return AVERROR_PATCHWELCOME;
        }
