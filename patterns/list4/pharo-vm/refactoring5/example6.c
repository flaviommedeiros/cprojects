#ifdef HAVE_MMX
if(video->have_mmx)
    		val = (((val << 1)+1) * slice->quant_scale * qmat[j]) >> 1;
		else
#endif
     		val = (((val << 1)+1) * slice->quant_scale * qmat[j]) >> 5;
