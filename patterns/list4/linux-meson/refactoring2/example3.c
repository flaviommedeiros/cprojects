#if (MESON_CPU_TYPE == MESON_CPU_TYPE_MESONG9TV) || (MESON_CPU_TYPE == MESON_CPU_TYPE_MESONG9BB)
if ((mode == TVMODE_480CVBS) || (mode == TVMODE_576CVBS))
#endif
{
    cvbs_cntl_output(0);
}
