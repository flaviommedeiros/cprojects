#ifdef HAVE_MMX
if(video->have_mmx)
		{
    		val = (((val << 1)+1) * slice->quant_scale * video->non_intra_quantizer_matrix[j]);
    		val = (val - 16) | 16;
		}
		else
#endif
		{
    		val = (((val << 1)+1) * slice->quant_scale * video->non_intra_quantizer_matrix[j]) >> 4;
    		val = (val - 1) | 1;
		}
