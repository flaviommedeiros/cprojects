if (!bit_test(bg_record->mp_bitmap, mp_bit)
#ifndef HAVE_BG_L_P
		    /* In BGQ if a nodeboard goes down you can no
		       longer use any block using that nodeboard in a
		       passthrough, so we need to remove it.
		    */
		    && !(has_pass = block_mp_passthrough(bg_record, mp_bit))
#endif
			)
			continue;
