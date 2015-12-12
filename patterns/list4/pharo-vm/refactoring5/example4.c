#ifdef HAVE_MMX
if(video->have_mmx)
  		bp[0] = val << (7 - video->dc_prec);
	else
#endif
  		bp[0] = val << (3 - video->dc_prec);
