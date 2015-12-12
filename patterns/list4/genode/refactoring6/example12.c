if ((png_ptr->transformations & PNG_GAMMA) &&
#if defined(PNG_READ_BACKGROUND_SUPPORTED)
      !((png_ptr->transformations & PNG_BACKGROUND) &&
      ((png_ptr->num_trans != 0) ||
      (png_ptr->color_type & PNG_COLOR_MASK_ALPHA))) &&
#endif
      (png_ptr->color_type != PNG_COLOR_TYPE_PALETTE))
      png_do_gamma(&(png_ptr->row_info), png_ptr->row_buf + 1,
         png_ptr->gamma_table, png_ptr->gamma_16_table,
         png_ptr->gamma_shift);
