#ifdef ASKITIS
if( !judy->depth && !base[slot * keysize] || judy->depth && ++depth == judy->depth )
#else
			if( !judy->depth && !base[slot * keysize + keysize - 1] || judy->depth && ++depth == judy->depth )
#endif
				return &node[-slot-1];
