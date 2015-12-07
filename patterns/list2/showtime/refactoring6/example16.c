if(gr->gr_dirty ||
       memcmp(&grc->grc_mtx, &rc->rc_mtx, sizeof(Mtx)) ||
       glw_renderer_clippers_cmp(grc, root)
#if NUM_STENCILERS > 0
       || glw_renderer_stencilers_cmp(grc, root)
#endif
#if NUM_FADERS > 0
       glw_renderer_faders_cmp(grc, root)
#endif
       ) {
      glw_renderer_tesselate(gr, root, rc, grc);
    }
