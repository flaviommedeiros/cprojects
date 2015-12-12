#ifdef HAVE_MMX
if(video->have_mmx)
	    	val = (val * slice->quant_scale * qmat[j]);
		else
#endif
    		val = (val * slice->quant_scale * qmat[j]) >> 4;
