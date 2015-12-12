if ((png_ptr->transformations & PNG_GAMMA) &&
#ifdef PNG_READ_RGB_TO_GRAY_SUPPORTED
      /* Because RGB_TO_GRAY does the gamma transform. */
      !(png_ptr->transformations & PNG_RGB_TO_GRAY) &&
#endif
#if defined(PNG_READ_BACKGROUND_SUPPORTED) ||\
   defined(PNG_READ_ALPHA_MODE_SUPPORTED)
      /* Because PNG_COMPOSE does the gamma transform if there is something to
       * do (if there is an alpha channel or transparency.)
       */
       !((png_ptr->transformations & PNG_COMPOSE) &&
       ((png_ptr->num_trans != 0) ||
       (png_ptr->color_type & PNG_COLOR_MASK_ALPHA))) &&
#endif
      /* Because png_init_read_transformations transforms the palette, unless
       * RGB_TO_GRAY will do the transform.
       */
       (png_ptr->color_type != PNG_COLOR_TYPE_PALETTE))
      png_do_gamma(row_info, png_ptr->row_buf + 1, png_ptr);
