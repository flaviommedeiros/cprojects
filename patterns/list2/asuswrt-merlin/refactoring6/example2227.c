if(
			!encoder->private_->disable_constant_subframes &&
#ifndef FLAC__INTEGER_ONLY_LIBRARY
			fixed_residual_bits_per_sample[1] == 0.0
#else
			fixed_residual_bits_per_sample[1] == FLAC__FP_ZERO
#endif
		) {
			/* the above means it's possible all samples are the same value; now double-check it: */
			unsigned i;
			signal_is_constant = true;
			for(i = 1; i < frame_header->blocksize; i++) {
				if(integer_signal[0] != integer_signal[i]) {
					signal_is_constant = false;
					break;
				}
			}
		}
