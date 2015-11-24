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
			base = (uchar *)(next & JUDY_mask);
			node = (JudySlot *)((next & JUDY_mask) + size);
			keysize = JUDY_key_size - (off & JUDY_key_mask);
			cnt = size / (sizeof(JudySlot) + keysize);
			slot = cnt;
			value = 0;

			if( judy->depth ) {
				value = src[depth++];
				off |= JUDY_key_mask;
				off++;
				value &= JudyMask[keysize];
			} else
			  do {
				value <<= 8;
				if( off < max )
					value |= buff[off];
			  } while( ++off & JUDY_key_mask );

			//  find slot > key

			while( slot-- ) {
				test = *(judyvalue *)(base + slot * keysize);
#if BYTE_ORDER == BIG_ENDIAN
				test >>= 8 * (JUDY_key_size - keysize); 
#else
				test &= JudyMask[keysize];
#endif
				if( test <= value )
					break;
			}
#ifndef ASKITIS
			judy->stack[judy->level].slot = slot;
#endif
			if( test == value ) {

				// is this a leaf?

				if( !judy->depth && !(value & 0xFF) || judy->depth && depth == judy->depth )
					return &node[-slot-1];

				next = node[-slot-1];
				continue;
			}

			return NULL;

		case JUDY_radix:
			table = (JudySlot  *)(next & JUDY_mask); // outer radix

			if( judy->depth )
				slot = (src[depth] >> ((JUDY_key_size - ++off & JUDY_key_mask) * 8)) & 0xff;
			else if( off < max )
				slot = buff[off++];
			else
				slot = 0;
#ifndef ASKITIS
			//	put radix slot on judy stack

			judy->stack[judy->level].slot = slot;
#endif
			if( (next = table[slot >> 4]) )
				table = (JudySlot  *)(next & JUDY_mask); // inner radix
			else
				return NULL;

			if( judy->depth )
				if( !(off & JUDY_key_mask) )
					depth++;

			if( !judy->depth && !slot || judy->depth && depth == judy->depth )	// leaf?
				if( table[slot & 0x0F] )	// occupied?
					return &table[slot & 0x0F];
				else
					return NULL;

			next = table[slot & 0x0F];
			continue;

#ifndef ASKITIS
		case JUDY_span:
			node = (JudySlot *)((next & JUDY_mask) + JudySize[JUDY_span]);
			base = (uchar *)(next & JUDY_mask);
			cnt = tst = JUDY_span_bytes;
			if( tst > (int)(max - off) )
				tst = max - off;
			value = strncmp((const char *)base, (const char *)(buff + off), tst);
			if( !value && tst < cnt && !base[tst] ) // leaf?
				return &node[-1];

			if( !value && tst == cnt ) {
				next = node[-1];
				off += cnt;
				continue;
			}
			return NULL;
#endif
		}
