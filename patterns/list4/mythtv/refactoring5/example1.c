#ifdef MMX
if (av_get_cpu_flags() & AV_CPU_FLAG_MMX2)
    {
        yv12_to_yuy2 = yv12_to_yuy2_mmxext;
        yuy2_to_yv12 = yuy2_to_yv12_mmxext;
        vfilter_chroma_332_packed422_scanline = vfilter_chroma_332_packed422_scanline_mmx;
    }
    else
#endif
    {
        yv12_to_yuy2 = yv12_to_yuy2_c;
        yuy2_to_yv12 = yuy2_to_yv12_c;
        vfilter_chroma_332_packed422_scanline = vfilter_chroma_332_packed422_scanline_c;
    }
