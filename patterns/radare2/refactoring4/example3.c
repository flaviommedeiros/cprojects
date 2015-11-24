#if BYTE_ORDER != BIG_ENDIAN
if( !judy->depth && !base[(slot - 1) * keysize] || judy->depth && ++depth == judy->depth )
#else
			if( !judy->depth && !base[(slot - 1) * keysize + keysize - 1] || judy->depth && ++depth == judy->depth )
#endif
				return &node[-slot];
