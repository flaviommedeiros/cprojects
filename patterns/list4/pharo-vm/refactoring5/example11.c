#ifdef HAVE_MMX
if(video->have_mmx)
	  	  			IDCT_mmx(slice->block[comp]);
				else
#endif
          			mpeg3video_idct_conversion(slice->block[comp]);
