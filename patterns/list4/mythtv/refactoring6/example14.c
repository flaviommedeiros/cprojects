if (s->current_picture->data[0]
#if FF_API_EMU_EDGE
        && !(s->avctx->flags&CODEC_FLAG_EMU_EDGE)
#endif
        ) {
        int w = s->avctx->width;
        int h = s->avctx->height;

        s->mpvencdsp.draw_edges(s->current_picture->data[0],
                                s->current_picture->linesize[0], w   , h   ,
                                EDGE_WIDTH  , EDGE_WIDTH  , EDGE_TOP | EDGE_BOTTOM);
        if (s->current_picture->data[2]) {
            s->mpvencdsp.draw_edges(s->current_picture->data[1],
                                    s->current_picture->linesize[1], w>>s->chroma_h_shift, h>>s->chroma_v_shift,
                                    EDGE_WIDTH>>s->chroma_h_shift, EDGE_WIDTH>>s->chroma_v_shift, EDGE_TOP | EDGE_BOTTOM);
            s->mpvencdsp.draw_edges(s->current_picture->data[2],
                                    s->current_picture->linesize[2], w>>s->chroma_h_shift, h>>s->chroma_v_shift,
                                    EDGE_WIDTH>>s->chroma_h_shift, EDGE_WIDTH>>s->chroma_v_shift, EDGE_TOP | EDGE_BOTTOM);
        }
    }
