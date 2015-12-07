#ifdef LIBVO_XV
if (instance->xv == 1 &&
	(chroma_width == width >> 1) && (chroma_height == height >> 1) &&
	!xv_check_extension (instance, FOURCC_YV12, "YV12") &&
	!xv_alloc_frames (instance, 3 * width * height / 2, FOURCC_YV12)) {
	instance->vo.setup_fbuf = xv_setup_fbuf;
	instance->vo.start_fbuf = x11_start_fbuf;
	instance->vo.draw = xv_draw_frame;
	instance->teardown = xv_teardown;
    } else if (instance->xv && (chroma_width == width >> 1) &&
	       !xv_check_extension (instance, FOURCC_UYVY, "UYVY") &&
	       !xv_alloc_frames (instance, 2 * width * height, FOURCC_UYVY)) {
	instance->vo.setup_fbuf = x11_setup_fbuf;
	instance->vo.start_fbuf = x11_start_fbuf;
	instance->vo.draw = xv_draw_frame;
	instance->teardown = xv_teardown;
	result->convert = mpeg2convert_uyvy;
    } else
#endif
    if (!x11_alloc_frames (instance, 1) || !x11_alloc_frames (instance, 0)) {
	int bpp;

	instance->vo.setup_fbuf = x11_setup_fbuf;
	instance->vo.start_fbuf = x11_start_fbuf;
	instance->vo.draw = x11_draw_frame;
	instance->teardown = x11_teardown;

#ifdef WORDS_BIGENDIAN
	if (instance->frame[0].ximage->byte_order != MSBFirst) {
	    fprintf (stderr, "No support for non-native byte order\n");
	    return 1;
	}
#else
	if (instance->frame[0].ximage->byte_order != LSBFirst) {
	    fprintf (stderr, "No support for non-native byte order\n");
	    return 1;
	}
#endif

	/*
	 * depth in X11 terminology land is the number of bits used to
	 * actually represent the colour.
	 *
	 * bpp in X11 land means how many bits in the frame buffer per
	 * pixel.
	 *
	 * ex. 15 bit color is 15 bit depth and 16 bpp. Also 24 bit
	 *     color is 24 bit depth, but can be 24 bpp or 32 bpp.
	 *
	 * If we have blue in the lowest bit then "obviously" RGB
	 * (the guy who wrote this convention never heard of endianness ?)
	 */

	bpp = ((instance->vinfo.depth == 24) ?
	       instance->frame[0].ximage->bits_per_pixel :
	       instance->vinfo.depth);
	result->convert =
	    mpeg2convert_rgb (((instance->frame[0].ximage->blue_mask & 1) ?
			       MPEG2CONVERT_RGB : MPEG2CONVERT_BGR), bpp);
	if (result->convert == NULL) {
	    fprintf (stderr, "%dbpp not supported\n", bpp);
	    return 1;
	}
    }
