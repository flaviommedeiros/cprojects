#ifdef ASKITIS
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
