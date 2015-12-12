static const u32 *filter_table[] = {
	vpp_filter_coefs_bicubic,
	vpp_filter_coefs_3point_triangle,
	vpp_filter_coefs_4point_triangle,
	vpp_filter_coefs_bilinear,
#if MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8
	vpp_filter_coefs_2point_binilear
#endif
};
