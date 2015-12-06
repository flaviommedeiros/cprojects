switch( type = next & 0x07 ) {
		case JUDY_1:
		case JUDY_2:
		case JUDY_4:
		case JUDY_8:
		case JUDY_16:
		case JUDY_32:
#ifdef ASKITIS
		case JUDY_64:
#endif
			keysize = JUDY_key_size - (off & JUDY_key_mask);
			cnt = size / (sizeof(JudySlot) + keysize);
			node = (JudySlot *)((next & JUDY_mask) + size);
			base = (uchar *)(next & JUDY_mask);

			//	move deleted slot to first slot

			while( slot ) {
				node[-slot-1] = node[-slot];
				memcpy (base + slot * keysize, base + (slot - 1) * keysize, keysize);
				slot--;
			}

			//	zero out first slot

			node[-1] = 0;
			memset (base, 0, keysize);

			if( node[-cnt] ) {	// does node have any slots left?
				judy->stack[judy->level].slot++;
				return judy_prv (judy);
			}

			judy_free (judy, base, type);
			judy->level--;
			continue;

		case JUDY_radix:
			table = (JudySlot  *)(next & JUDY_mask);
			inner = (JudySlot *)(table[slot >> 4] & JUDY_mask);
			inner[slot & 0x0F] = 0;
			high = slot & 0xF0;

			for( cnt = 16; cnt--; )
				if( inner[cnt] )
					return judy_prv (judy);

			judy_free (judy, inner, JUDY_radix);
			table[slot >> 4] = 0;

			for( cnt = 16; cnt--; )
				if( table[cnt] )
					return judy_prv (judy);

			judy_free (judy, table, JUDY_radix);
			judy->level--;
			continue;

#ifndef ASKITIS
		case JUDY_span:
			base = (uchar *)(next & JUDY_mask);
			judy_free (judy, base, type);
			judy->level--;
			continue;
#endif
		}
