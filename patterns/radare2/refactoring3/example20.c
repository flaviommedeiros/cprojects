switch( next & 0x07 ) {
		case JUDY_1:
		case JUDY_2:
		case JUDY_4:
		case JUDY_8:
		case JUDY_16:
		case JUDY_32:
#ifdef ASKITIS
		case JUDY_64:
#endif
			node = (JudySlot *)((next & JUDY_mask) + size);
			if( !slot || !node[-slot] ) {
				judy->level--;
				continue;
			}

			base = (uchar *)(next & JUDY_mask);
			judy->stack[judy->level].slot--;
			keysize = JUDY_key_size - (off & JUDY_key_mask);

#if BYTE_ORDER != BIG_ENDIAN
			if( !judy->depth && !base[(slot - 1) * keysize] || judy->depth && ++depth == judy->depth )
#else
			if( !judy->depth && !base[(slot - 1) * keysize + keysize - 1] || judy->depth && ++depth == judy->depth )
#endif
				return &node[-slot];
			return judy_last (judy, node[-slot], (off | JUDY_key_mask) + 1, depth);

		case JUDY_radix:
			table = (JudySlot *)(next & JUDY_mask);

			if( judy->depth )
			  if( !((off + 1) & JUDY_key_mask) )
				depth++;

			while( slot-- ) {
			  judy->stack[judy->level].slot--;
			  if( (inner = (JudySlot *)(table[slot >> 4] & JUDY_mask)) )
				if( inner[slot & 0x0F] )
				  if( !judy->depth && !slot || judy->depth && depth == judy->depth )
					return &inner[0];
				  else
				    return judy_last(judy, inner[slot & 0x0F], off + 1, depth);
			}

			judy->level--;
			continue;

#ifndef ASKITIS
		case JUDY_span:
			judy->level--;
			continue;
#endif
		}
