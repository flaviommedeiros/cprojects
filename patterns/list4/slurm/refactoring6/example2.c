if (!wait || (bg_record->state == BG_BLOCK_FREE)
#ifndef HAVE_BGL
		    ||  (bg_record->state & BG_BLOCK_ERROR_FLAG)
#endif
			) {
			break;
		}
