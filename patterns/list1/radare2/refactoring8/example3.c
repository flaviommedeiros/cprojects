int JudySize[] = {
	(JUDY_slot_size * 16),						// JUDY_radix node size
	(JUDY_slot_size + JUDY_key_size),			// JUDY_1 node size
	(2 * JUDY_slot_size + 2 * JUDY_key_size),
	(4 * JUDY_slot_size + 4 * JUDY_key_size),
	(8 * JUDY_slot_size + 8 * JUDY_key_size),
	(16 * JUDY_slot_size + 16 * JUDY_key_size),
	(32 * JUDY_slot_size + 32 * JUDY_key_size),
#ifndef ASKITIS
	(JUDY_span_bytes + JUDY_slot_size)
#else
	(64 * JUDY_slot_size + 64 * JUDY_key_size)
#endif
};
