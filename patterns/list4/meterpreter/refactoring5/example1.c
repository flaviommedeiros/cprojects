#ifdef LDBL_IMPLICIT_NBIT
if (e == 0)
					u.bits.exp++;
				else
#endif
				INC_MANH(u, 1llu << (MANH_SIZE - e - 1));
