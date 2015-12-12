switch (c->fmt) {
        case ZMBV_FMT_8BPP:
            for (j = 0; j < 256; j++)
                AV_WN32(&frame->data[1][j * 4], 0xFFU << 24 | AV_RB24(&c->pal[j * 3]));
        case ZMBV_FMT_15BPP:
        case ZMBV_FMT_16BPP:
#ifdef ZMBV_ENABLE_24BPP
        case ZMBV_FMT_24BPP:
#endif
        case ZMBV_FMT_32BPP:
            av_image_copy_plane(out, frame->linesize[0], src, c->stride,
                                c->stride, c->height);
            break;
        default:
            av_log(avctx, AV_LOG_ERROR, "Cannot handle format %i\n", c->fmt);
        }
