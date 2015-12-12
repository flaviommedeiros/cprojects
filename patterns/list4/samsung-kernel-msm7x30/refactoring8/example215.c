static struct v4l2_pix_format vicam_mode[] = {
	{ 256, 122, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
		.bytesperline = 256,
		.sizeimage = 256 * 122,
		.colorspace = V4L2_COLORSPACE_SRGB,},
	/* 2 modes with somewhat more square pixels */
	{ 256, 200, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
		.bytesperline = 256,
		.sizeimage = 256 * 200,
		.colorspace = V4L2_COLORSPACE_SRGB,},
	{ 256, 240, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
		.bytesperline = 256,
		.sizeimage = 256 * 240,
		.colorspace = V4L2_COLORSPACE_SRGB,},
#if 0   /* This mode has extremely non square pixels, testing use only */
	{ 512, 122, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
		.bytesperline = 512,
		.sizeimage = 512 * 122,
		.colorspace = V4L2_COLORSPACE_SRGB,},
#endif
	{ 512, 244, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
		.bytesperline = 512,
		.sizeimage = 512 * 244,
		.colorspace = V4L2_COLORSPACE_SRGB,},
};
