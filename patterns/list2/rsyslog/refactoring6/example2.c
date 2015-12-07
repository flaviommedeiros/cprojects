if ((ip6->s6_addr32[3] & (u_int32_t) htonl((0xffffffff << (32 - bits)))) == net->s_addr &&
#if BYTE_ORDER == LITTLE_ENDIAN
				    (ip6->s6_addr32[2] == (u_int32_t)0xffff0000) &&
#else
				    (ip6->s6_addr32[2] == (u_int32_t)0x0000ffff) &&
#endif
				    (ip6->s6_addr32[1] == 0) && (ip6->s6_addr32[0] == 0))
					return 1;
				else
					return 0;
