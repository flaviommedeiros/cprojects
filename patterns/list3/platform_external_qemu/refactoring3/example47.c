switch (cinfo->out_color_space) {
  case JCS_GRAYSCALE:
    cinfo->out_color_components = 1;
    if (cinfo->jpeg_color_space == JCS_GRAYSCALE ||
	cinfo->jpeg_color_space == JCS_YCbCr) {
      cconvert->pub.color_convert = grayscale_convert;
      /* For color->grayscale conversion, only the Y (0) component is needed */
      for (ci = 1; ci < cinfo->num_components; ci++)
	cinfo->comp_info[ci].component_needed = FALSE;
    } else
      ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
    break;

  case JCS_RGB:
    cinfo->out_color_components = RGB_PIXELSIZE;
    if (cinfo->jpeg_color_space == JCS_YCbCr) {
      cconvert->pub.color_convert = ycc_rgb_convert;
      build_ycc_rgb_table(cinfo);
    } else if (cinfo->jpeg_color_space == JCS_GRAYSCALE) {
      cconvert->pub.color_convert = gray_rgb_convert;
    } else if (cinfo->jpeg_color_space == JCS_RGB && RGB_PIXELSIZE == 3) {
      cconvert->pub.color_convert = null_convert;
    } else
      ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
    break;

#ifdef ANDROID_RGB
  case JCS_RGBA_8888:
    cinfo->out_color_components = 4;
    if (cinfo->jpeg_color_space == JCS_YCbCr) {
      cconvert->pub.color_convert = ycc_rgba_8888_convert;
      build_ycc_rgb_table(cinfo);
    } else if (cinfo->jpeg_color_space == JCS_GRAYSCALE) {
      cconvert->pub.color_convert = gray_rgba_8888_convert;
    } else if (cinfo->jpeg_color_space == JCS_RGB) {
      cconvert->pub.color_convert = rgb_rgba_8888_convert;
    } else
      ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
    break;

  case JCS_RGB_565:
    cinfo->out_color_components = RGB_PIXELSIZE;
    if (cinfo->dither_mode == JDITHER_NONE) {
      if (cinfo->jpeg_color_space == JCS_YCbCr) {
        cconvert->pub.color_convert = ycc_rgb_565_convert;
        build_ycc_rgb_table(cinfo);
      } else if (cinfo->jpeg_color_space == JCS_GRAYSCALE) {
        cconvert->pub.color_convert = gray_rgb_565_convert;
      } else if (cinfo->jpeg_color_space == JCS_RGB) {
        cconvert->pub.color_convert = rgb_rgb_565_convert;
      } else
        ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
    } else {
      /* only ordered dither is supported */
      if (cinfo->jpeg_color_space == JCS_YCbCr) {
        cconvert->pub.color_convert = ycc_rgb_565D_convert;
        build_ycc_rgb_table(cinfo);
      } else if (cinfo->jpeg_color_space == JCS_GRAYSCALE) {
        cconvert->pub.color_convert = gray_rgb_565D_convert;
      } else if (cinfo->jpeg_color_space == JCS_RGB) {
        cconvert->pub.color_convert = rgb_rgb_565D_convert;
      } else
        ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
    }
    break;
#endif
    
  case JCS_CMYK:
    cinfo->out_color_components = 4;
    if (cinfo->jpeg_color_space == JCS_YCCK) {
      cconvert->pub.color_convert = ycck_cmyk_convert;
      build_ycc_rgb_table(cinfo);
    } else if (cinfo->jpeg_color_space == JCS_CMYK) {
      cconvert->pub.color_convert = null_convert;
    } else
      ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
    break;

  default:
    /* Permit null conversion to same output space */
    if (cinfo->out_color_space == cinfo->jpeg_color_space) {
      cinfo->out_color_components = cinfo->num_components;
      cconvert->pub.color_convert = null_convert;
    } else			/* unsupported non-null conversion */
      ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
    break;
  }
