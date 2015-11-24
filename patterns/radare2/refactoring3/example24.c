switch( *next & 0x07 ) {
		default:
			size = JudySize[*next & 0x07];
			keysize = JUDY_key_size - (off & JUDY_key_mask);
			cnt = size / (sizeof(JudySlot) + keysize);
			base = (uchar *)(*next & JUDY_mask);
			node = (JudySlot *)((*next & JUDY_mask) + size);
			start = off;
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
			if( test == value ) {		// new key is equal to slot key
				next = &node[-slot-1];

				// is this a leaf?

				if( !judy->depth && !(value & 0xFF) || judy->depth && depth == judy->depth ) {
				  return next;
				}

				continue;
			}

			//	if this node is not full
			//	open up cell after slot

			if( !node[-1] ) {
		 	  memmove(base, base + keysize, slot * keysize);	// move keys less than new key down one slot
#if BYTE_ORDER != BIG_ENDIAN
			  memcpy(base + slot * keysize, &value, keysize);	// copy new key into slot
#else
			  test = value;
			  idx = keysize;

			  while( idx-- )
				  base[slot * keysize + idx] = test, test >>= 8;
#endif
			  for( idx = 0; idx < slot; idx++ )
				node[-idx-1] = node[-idx-2];// copy tree ptrs/cells down one slot

			  node[-slot-1] = 0;			// set new tree ptr/cell
			  next = &node[-slot-1];

			  if( !judy->depth && !(value & 0xFF) || judy->depth && depth == judy->depth ) {
			  	return next;
			  }

			  continue;
			}

			if( size < JudySize[JUDY_max] ) {
			  next = judy_promote (judy, next, slot+1, value, keysize);

			  if( !judy->depth && !(value & 0xFF) || judy->depth && depth == judy->depth ) {
				return next;
			  }

			  continue;
			}

			//	split full maximal node into JUDY_radix nodes
			//  loop to reprocess new insert

			judy_splitnode (judy, next, size, keysize, depth);
#ifndef ASKITIS
			judy->level--;
#endif
			off = start;
			if( judy->depth )
				depth--;
			continue;
		
		case JUDY_radix:
			table = (JudySlot *)(*next & JUDY_mask); // outer radix

			if( judy->depth )
				slot = (src[depth] >> ((JUDY_key_size - ++off & JUDY_key_mask) * 8)) & 0xff;
			else if( off < max )
				slot = buff[off++];
			else
				slot = 0, off++;

			if( judy->depth )
				if( !(off & JUDY_key_mask) )
					depth++;

			// allocate inner radix if empty

			if( !table[slot >> 4] )
				table[slot >> 4] = (JudySlot)judy_alloc (judy, JUDY_radix) | JUDY_radix;

			table = (JudySlot *)(table[slot >> 4] & JUDY_mask);
#ifndef ASKITIS
			judy->stack[judy->level].slot = slot;
#endif
			next = &table[slot & 0x0F];

			if( !judy->depth && !slot || judy->depth && depth == judy->depth ) { // leaf?
				return next;
			}

			continue;

#ifndef ASKITIS
		case JUDY_span:
			base = (uchar *)(*next & JUDY_mask);
			node = (JudySlot *)((*next & JUDY_mask) + JudySize[JUDY_span]);
			cnt = JUDY_span_bytes;
			tst = cnt;

			if( tst > (int)(max - off) )
				tst = max - off;

			value = strncmp((const char *)base, (const char *)(buff + off), tst);

			if( !value && tst < cnt && !base[tst] ) // leaf?
				return &node[-1];

			if( !value && tst == cnt ) {
				next = &node[-1];
				off += cnt;
				continue;
			}

			//	bust up JUDY_span node and produce JUDY_1 nodes
			//	then loop to reprocess insert

			judy_splitspan (judy, next, base);
			judy->level--;
			continue;
#endif
		}
