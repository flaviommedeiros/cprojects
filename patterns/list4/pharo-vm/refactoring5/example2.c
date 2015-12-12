#ifdef HAVE_MMX
if(video->have_mmx)
		{
    		val = (val * slice->quant_scale * video->intra_quantizer_matrix[j]) << 1;
    		val = (val - 16) | 16;
		}
		else
#endif
		{
    		val = (val * slice->quant_scale * video->intra_quantizer_matrix[j]) >> 3;
    		val = (val - 1) | 1;
		}
