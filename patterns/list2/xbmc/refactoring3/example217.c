switch(c->fmt) {
        case ZMBV_FMT_8BPP:
            for(j = 0; j < c->height; j++) {
                for(i = 0; i < c->width; i++) {
                    out[i * 3 + 0] = c->pal[(*src) * 3 + 0];
                    out[i * 3 + 1] = c->pal[(*src) * 3 + 1];
                    out[i * 3 + 2] = c->pal[(*src) * 3 + 2];
                    src++;
                }
                out += c->pic.linesize[0];
            }
            break;
        case ZMBV_FMT_15BPP:
            for(j = 0; j < c->height; j++) {
                for(i = 0; i < c->width; i++) {
                    uint16_t tmp = AV_RL16(src);
                    src += 2;
                    out[i * 3 + 0] = (tmp & 0x7C00) >> 7;
                    out[i * 3 + 1] = (tmp & 0x03E0) >> 2;
                    out[i * 3 + 2] = (tmp & 0x001F) << 3;
                }
                out += c->pic.linesize[0];
            }
            break;
        case ZMBV_FMT_16BPP:
            for(j = 0; j < c->height; j++) {
                for(i = 0; i < c->width; i++) {
                    uint16_t tmp = AV_RL16(src);
                    src += 2;
                    out[i * 3 + 0] = (tmp & 0xF800) >> 8;
                    out[i * 3 + 1] = (tmp & 0x07E0) >> 3;
                    out[i * 3 + 2] = (tmp & 0x001F) << 3;
                }
                out += c->pic.linesize[0];
            }
            break;
#ifdef ZMBV_ENABLE_24BPP
        case ZMBV_FMT_24BPP:
            for(j = 0; j < c->height; j++) {
                memcpy(out, src, c->width * 3);
                src += c->width * 3;
                out += c->pic.linesize[0];
            }
            break;
#endif //ZMBV_ENABLE_24BPP
        case ZMBV_FMT_32BPP:
            for(j = 0; j < c->height; j++) {
                for(i = 0; i < c->width; i++) {
                    uint32_t tmp = AV_RL32(src);
                    src += 4;
                    AV_WB24(out+(i*3), tmp);
                }
                out += c->pic.linesize[0];
            }
            break;
        default:
            av_log(avctx, AV_LOG_ERROR, "Cannot handle format %i\n", c->fmt);
        }
