switch(c->fmt) {
        case ZMBV_FMT_8BPP:
            c->bpp = 8;
            c->decode_intra = zmbv_decode_intra;
            c->decode_xor = zmbv_decode_xor_8;
            break;
        case ZMBV_FMT_15BPP:
        case ZMBV_FMT_16BPP:
            c->bpp = 16;
            c->decode_intra = zmbv_decode_intra;
            c->decode_xor = zmbv_decode_xor_16;
            break;
#ifdef ZMBV_ENABLE_24BPP
        case ZMBV_FMT_24BPP:
            c->bpp = 24;
            c->decode_intra = zmbv_decode_intra;
            c->decode_xor = zmbv_decode_xor_24;
            break;
#endif //ZMBV_ENABLE_24BPP
        case ZMBV_FMT_32BPP:
            c->bpp = 32;
            c->decode_intra = zmbv_decode_intra;
            c->decode_xor = zmbv_decode_xor_32;
            break;
        default:
            c->decode_intra = NULL;
            c->decode_xor = NULL;
            av_log(avctx, AV_LOG_ERROR, "Unsupported (for now) format %i\n", c->fmt);
            return -1;
        }
