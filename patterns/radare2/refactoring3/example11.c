switch( type ) {
		case JUDY_1:
		case JUDY_2:
		case JUDY_4:
		case JUDY_8:
		case JUDY_16:
		case JUDY_32:
#ifdef ASKITIS
		case JUDY_64:
#endif
			keysize = JUDY_key_size - (judy->stack[idx].off & JUDY_key_mask);
			base = (uchar *)(judy->stack[idx].next & JUDY_mask);

			if( judy->depth ) {
				value = *(judyvalue *)(base + slot * keysize);
				value &= JudyMask[keysize];
				dest[depth++] |= value;
				len += keysize;

				if( depth < judy->depth )
					continue;

				return len;
			}

#if BYTE_ORDER != BIG_ENDIAN
			off = keysize;

			while( off-- && len < max )
				if( buff[len] = base[slot * keysize + off] )
					len++;
				else
					break;
#else
			for( off = 0; off < keysize && len < max; off++ )
				if( buff[len] = base[slot * keysize + off] )
					len++;
				else
					break;
#endif
			continue;

		case JUDY_radix:
			if( judy->depth ) {
				dest[depth] |= (judyvalue)slot << (JUDY_key_size - (++len & JUDY_key_mask)) * 8;
		  		if( !(len & JUDY_key_mask) )
					depth++;
				if( depth < judy->depth )
					continue;

				return len;
			}

			if( !slot )
				break;
			buff[len++] = (uchar)slot;
			continue;

#ifndef ASKITIS
		case JUDY_span:
			base = (uchar *)(judy->stack[idx].next & JUDY_mask);

			for( slot = 0; slot < JUDY_span_bytes && base[slot]; slot++ )
			  if( len < max )
				buff[len++] = base[slot];
			continue;
#endif
		}
