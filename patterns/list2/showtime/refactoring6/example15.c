if(root->gr_need_sw_clip
#if NUM_FADERS > 0
     || root->gr_active_faders
#endif
#if NUM_STENCILERS > 0
     || root->gr_stencil_width
#endif
     ) {
    glw_renderer_cache_t *grc = glw_renderer_get_cache(root, gr);

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

    if(grc->grc_blurred)
      flags |= GLW_RENDER_BLUR_ATTRIBUTE;

    if(grc->grc_colored)
      flags |= GLW_RENDER_COLOR_ATTRIBUTES;

#if NUM_STENCILERS > 0
    if(root->gr_stencil_width)
      tex2 = root->gr_stencil_texture;
#endif
    add_job(root, NULL, tex, tex2,
            rgb_mul, rgb_off, alpha, blur,
            grc->grc_vertices, grc->grc_num_vertices,
            NULL, 0, flags, gpa, rc, GLW_DRAW_TRIANGLES, rc->rc_zindex);
  } else {
    add_job(root, &rc->rc_mtx, tex, tex2, rgb_mul, rgb_off, alpha, blur,
            gr->gr_vertices, gr->gr_num_vertices,
            gr->gr_indices,  gr->gr_num_triangles,
            flags, gpa, rc, GLW_DRAW_TRIANGLES, rc->rc_zindex);
  }
