#ifdef INPUT_SMOOTHING_SUPPORTED
if (cinfo->smoothing_factor) {
	downsample->methods[ci] = fullsize_smooth_downsample;
	downsample->pub.need_context_rows = TRUE;
      } else
#endif
	downsample->methods[ci] = fullsize_downsample;
