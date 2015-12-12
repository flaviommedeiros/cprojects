static av_always_inline
void mpeg_motion_internal(MpegEncContext *s,
                          uint8_t *dest_y,
                          uint8_t *dest_cb,
                          uint8_t *dest_cr,
                          int field_based,
                          int bottom_field,
                          int field_select,
                          uint8_t **ref_picture,
                          op_pixels_func (*pix_op)[4],
                          int motion_x,
                          int motion_y,
                          int h,
                          int is_mpeg12,
                          int mb_y)
{
    uint8_t *ptr_y, *ptr_cb, *ptr_cr;
    int dxy, uvdxy, mx, my, src_x, src_y,
        uvsrc_x, uvsrc_y, v_edge_pos;
    ptrdiff_t uvlinesize, linesize;

#if 0
    if (s->quarter_sample) {
        motion_x >>= 1;
        motion_y >>= 1;
    }
#endif

    v_edge_pos = s->v_edge_pos >> field_based;
    linesize   = s->current_picture.f->linesize[0] << field_based;
    uvlinesize = s->current_picture.f->linesize[1] << field_based;

    dxy   = ((motion_y & 1) << 1) | (motion_x & 1);
    src_x = s->mb_x * 16 + (motion_x >> 1);
    src_y = (mb_y << (4 - field_based)) + (motion_y >> 1);

    if (!is_mpeg12 && s->out_format == FMT_H263) {
        if ((s->workaround_bugs & FF_BUG_HPEL_CHROMA) && field_based) {
            mx      = (motion_x >> 1) | (motion_x & 1);
            my      = motion_y >> 1;
            uvdxy   = ((my & 1) << 1) | (mx & 1);
            uvsrc_x = s->mb_x * 8 + (mx >> 1);
            uvsrc_y = (mb_y << (3 - field_based)) + (my >> 1);
        } else {
            uvdxy   = dxy | (motion_y & 2) | ((motion_x & 2) >> 1);
            uvsrc_x = src_x >> 1;
            uvsrc_y = src_y >> 1;
        }
    // Even chroma mv's are full pel in H261
    } else if (!is_mpeg12 && s->out_format == FMT_H261) {
        mx      = motion_x / 4;
        my      = motion_y / 4;
        uvdxy   = 0;
        uvsrc_x = s->mb_x * 8 + mx;
        uvsrc_y = mb_y * 8 + my;
    } else {
        if (s->chroma_y_shift) {
            mx      = motion_x / 2;
            my      = motion_y / 2;
            uvdxy   = ((my & 1) << 1) | (mx & 1);
            uvsrc_x = s->mb_x * 8 + (mx >> 1);
            uvsrc_y = (mb_y << (3 - field_based)) + (my >> 1);
        } else {
            if (s->chroma_x_shift) {
                // Chroma422
                mx      = motion_x / 2;
                uvdxy   = ((motion_y & 1) << 1) | (mx & 1);
                uvsrc_x = s->mb_x * 8 + (mx >> 1);
                uvsrc_y = src_y;
            } else {
                // Chroma444
                uvdxy   = dxy;
                uvsrc_x = src_x;
                uvsrc_y = src_y;
            }
        }
    }

    ptr_y  = ref_picture[0] + src_y * linesize + src_x;
    ptr_cb = ref_picture[1] + uvsrc_y * uvlinesize + uvsrc_x;
    ptr_cr = ref_picture[2] + uvsrc_y * uvlinesize + uvsrc_x;

    if ((unsigned)src_x >= FFMAX(s->h_edge_pos - (motion_x & 1) - 15   , 0) ||
        (unsigned)src_y >= FFMAX(   v_edge_pos - (motion_y & 1) - h + 1, 0)) {
        if (is_mpeg12 ||
            s->codec_id == AV_CODEC_ID_MPEG2VIDEO ||
            s->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
            av_log(s->avctx, AV_LOG_DEBUG,
                   "MPEG motion vector out of boundary (%d %d)\n", src_x,
                   src_y);
            return;
        }
        src_y = (unsigned)src_y << field_based;
        s->vdsp.emulated_edge_mc(s->sc.edge_emu_buffer, ptr_y,
                                 s->linesize, s->linesize,
                                 17, 17 + field_based,
                                 src_x, src_y,
                                 s->h_edge_pos, s->v_edge_pos);
        ptr_y = s->sc.edge_emu_buffer;
        if (!CONFIG_GRAY || !(s->avctx->flags & AV_CODEC_FLAG_GRAY)) {
            uint8_t *ubuf = s->sc.edge_emu_buffer + 18 * s->linesize;
            uint8_t *vbuf = ubuf + 9 * s->uvlinesize;
            uvsrc_y = (unsigned)uvsrc_y << field_based;
            s->vdsp.emulated_edge_mc(ubuf, ptr_cb,
                                     s->uvlinesize, s->uvlinesize,
                                     9, 9 + field_based,
                                     uvsrc_x, uvsrc_y,
                                     s->h_edge_pos >> 1, s->v_edge_pos >> 1);
            s->vdsp.emulated_edge_mc(vbuf, ptr_cr,
                                     s->uvlinesize, s->uvlinesize,
                                     9, 9 + field_based,
                                     uvsrc_x, uvsrc_y,
                                     s->h_edge_pos >> 1, s->v_edge_pos >> 1);
            ptr_cb = ubuf;
            ptr_cr = vbuf;
        }
    }

    /* FIXME use this for field pix too instead of the obnoxious hack which
     * changes picture.data */
    if (bottom_field) {
        dest_y  += s->linesize;
        dest_cb += s->uvlinesize;
        dest_cr += s->uvlinesize;
    }

    if (field_select) {
        ptr_y  += s->linesize;
        ptr_cb += s->uvlinesize;
        ptr_cr += s->uvlinesize;
    }

    pix_op[0][dxy](dest_y, ptr_y, linesize, h);

    if (!CONFIG_GRAY || !(s->avctx->flags & AV_CODEC_FLAG_GRAY)) {
        pix_op[s->chroma_x_shift][uvdxy]
            (dest_cb, ptr_cb, uvlinesize, h >> s->chroma_y_shift);
        pix_op[s->chroma_x_shift][uvdxy]
            (dest_cr, ptr_cr, uvlinesize, h >> s->chroma_y_shift);
    }
    if (!is_mpeg12 && (CONFIG_H261_ENCODER || CONFIG_H261_DECODER) &&
        s->out_format == FMT_H261) {
        ff_h261_loop_filter(s);
    }
}
