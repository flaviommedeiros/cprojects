static const tvi_info_t *const tvi_driver_list[]={
#if HAVE_TV_V4L2
    &tvi_info_v4l2,
#endif
    &tvi_info_dummy,
    NULL
};
