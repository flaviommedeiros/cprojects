#ifndef ASKITIS
if( off & JUDY_key_mask )
	 if( judy->depth || off <= max ) {
#else
	  while( off <= max ) {
#endif
		base = judy_alloc (judy, JUDY_1);
		keysize = JUDY_key_size - (off & JUDY_key_mask);
		node = (JudySlot  *)(base + JudySize[JUDY_1]);
		*next = (JudySlot)base | JUDY_1;

		//	fill in slot 0 with bytes of key

		if( judy->depth ) {
			value = src[depth];
#if BYTE_ORDER != BIG_ENDIAN
			  memcpy(base, &value, keysize);	// copy new key into slot
#else
			  while( keysize-- )
				  base[keysize] = value, value >>= 8;
#endif
		} else {
#if BYTE_ORDER != BIG_ENDIAN
		  while( keysize )
			if( off + keysize <= max )
				*base++ = buff[off + --keysize];
			else
				base++, --keysize;
#else
		  tst = keysize;

		  if( tst > (int)(max - off) )
			tst = max - off;

		  memcpy (base, buff + off, tst);
#endif
		}
#ifndef ASKITIS
		if( judy->level < judy->max )
			judy->level++;
		judy->stack[judy->level].next = *next;
		judy->stack[judy->level].slot = 0;
		judy->stack[judy->level].off = off;
#endif
		next = &node[-1];

		off |= JUDY_key_mask;
		depth++;
		off++;
	}

	//	produce span nodes to consume rest of key
	//  or judy_1 nodes if not string tree

#ifndef ASKITIS
	if( !judy->depth )
	  while( off <= max ) {
		base = judy_alloc (judy, JUDY_span);
		*next = (JudySlot)base | JUDY_span;
		node = (JudySlot  *)(base + JudySize[JUDY_span]);
		cnt = tst = JUDY_span_bytes;
		if( tst > (int)(max - off) )
			tst = max - off;
		memcpy (base, buff + off, tst);

		if( judy->level < judy->max )
			judy->level++;
		judy->stack[judy->level].next = *next;
		judy->stack[judy->level].slot = 0;
		judy->stack[judy->level].off = off;
		next = &node[-1];
		off += tst;
		depth++;

		if( !base[cnt-1] )	// done on leaf
			break;
	  }
	else
	  while( depth < judy->depth ) {
		base = judy_alloc (judy, JUDY_1);
		node = (JudySlot  *)(base + JudySize[JUDY_1]);
		*next = (JudySlot)base | JUDY_1;

		//	fill in slot 0 with bytes of key

		*(judyvalue *)base = src[depth];

		if( judy->level < judy->max )
			judy->level++;
		judy->stack[judy->level].next = *next;
		judy->stack[judy->level].slot = 0;
		judy->stack[judy->level].off = off;
		next = &node[-1];
		off |= JUDY_key_mask;
		depth++;
		off++;
	  }
#endif

	return next;
}
