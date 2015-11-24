inline void rc4(
#ifdef RC4_USE_LOCAL
                __local uint *restrict state,
#endif
                const uint *restrict key,
#ifdef RC4_IN_PLACE
                uint *buf
#else
                MAYBE_CONSTANT uint *restrict in,
                __global uint *restrict out
#endif
	)
{
	uint x;
	uint y = 0;
	uint index1 = 0;
	uint index2 = 0;
#ifndef RC4_USE_LOCAL
	uint state[256/4];
#endif

	/* RC4_init() */
#ifdef RC4_IV32
	for (x = 0; x < 256/4; x++)
		state[x] = rc4_iv[x];
#else
	for (x = 0; x < 256; x++)
		PUTCHAR_L(state, x, x);
#endif

	/* RC4_set_key() 406ms */
#ifdef RC4_UNROLLED_KEY
	/* Unrolled for hard-coded key length 16 */
	for (x = 0; x < 256; x++) {
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_and_inc(x);
		swap_no_inc(x);
		index1 = 0;
	}
#else
	for (x = 0; x < 256; x++)
		swap_state(x);
#endif

	/* RC4() 76ms for 32 bytes in-place */
#ifdef RC4_UNROLLED
	/* Unrolled to 32-bit xor */
	for (x = 1; x <= RC4_BUFLEN; x++) {
		uint xor_word;

		y = (GETCHAR_L(state, x) + y) & 255;
		swap_byte(x, y);
		xor_word = GETCHAR_L(state, (GETCHAR_L(state, x) + GETCHAR_L(state, y)) & 255);
		x++;

		y = (GETCHAR_L(state, x) + y) & 255;
		swap_byte(x, y);
		xor_word += GETCHAR_L(state, (GETCHAR_L(state, x) + GETCHAR_L(state, y)) & 255) << 8;
		x++;

		y = (GETCHAR_L(state, x) + y) & 255;
		swap_byte(x, y);
		xor_word += GETCHAR_L(state, (GETCHAR_L(state, x) + GETCHAR_L(state, y)) & 255) << 16;
		x++;

		y = (GETCHAR_L(state, x) + y) & 255;
		swap_byte(x, y);
		xor_word += GETCHAR_L(state, (GETCHAR_L(state, x) + GETCHAR_L(state, y)) & 255) << 24;

#ifdef RC4_IN_PLACE
		*buf++ ^= xor_word;
#else
		*out++ = *in++ ^ xor_word;
#endif
	}
#else /* RC4_UNROLLED */
#pragma unroll
	for (x = 1; x <= RC4_BUFLEN; x++) {
		y = (GETCHAR_L(state, x) + y) & 255;
		swap_byte(x, y);
#ifdef RC4_IN_PLACE
		XORCHAR(buf, x - 1, GETCHAR_L(state, (GETCHAR_L(state, x) + GETCHAR_L(state, y)) & 255));
#else
		PUTCHAR_G(out, x - 1, GETCHAR_MC(in, x - 1) ^ (GETCHAR_L(state, (GETCHAR_L(state, x) + GETCHAR_L(state, y)) & 255)));
#endif
	}
#endif /* RC4_UNROLLED */
}
