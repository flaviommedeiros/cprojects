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
			cnt = size / (sizeof(JudySlot) + keysize);
			node = (JudySlot *)((next & JUDY_mask) + size);
			base = (uchar *)(next & JUDY_mask);
			if( ++slot < cnt )
#if BYTE_ORDER != BIG_ENDIAN
				if( !judy->depth && !base[slot * keysize] || judy->depth && ++depth == judy->depth )
#else
				if( !judy->depth && !base[slot * keysize + keysize - 1] || judy->depth && ++depth == judy->depth )
#endif
				{
					judy->stack[judy->level].slot = slot;
					return &node[-slot - 1];
				} else {
					judy->stack[judy->level].slot = slot;
					return judy_first (judy, node[-slot-1], (off | JUDY_key_mask) + 1, depth);
				}
			judy->level--;
			continue;

		case JUDY_radix:
			table = (JudySlot *)(next & JUDY_mask);

			if( judy->depth )
			  if( !((off+1) & JUDY_key_mask) )
				depth++; 

			while( ++slot < 256 )
			  if( (inner = (JudySlot *)(table[slot >> 4] & JUDY_mask)) ) {
				if( inner[slot & 0x0F] ) {
				  judy->stack[judy->level].slot = slot;
				  if( !judy->depth || depth < judy->depth )
					return judy_first(judy, inner[slot & 0x0F], off + 1, depth);
				  return &inner[slot & 0x0F];
				}
			  } else
				slot |= 0x0F;

			judy->level--;
			continue;
#ifndef ASKITIS
		case JUDY_span:
			judy->level--;
			continue;
#endif
		}
