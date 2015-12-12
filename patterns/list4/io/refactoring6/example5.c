if (m_pos[3] != *ip++ || m_pos[4] != *ip++ || m_pos[5] != *ip++ ||
			m_pos[6] != *ip++ || m_pos[7] != *ip++ || m_pos[8] != *ip++
#ifdef LZO1Y
			|| m_pos[ 9] != *ip++ || m_pos[10] != *ip++ || m_pos[11] != *ip++
			|| m_pos[12] != *ip++ || m_pos[13] != *ip++ || m_pos[14] != *ip++
#endif
		   )
		{
			--ip;
			m_len = pd(ip, ii);
			assert(m_len >= 3); assert(m_len <= M2_MAX_LEN);

			if (m_off <= M2_MAX_OFFSET)
			{
				m_off -= 1;
#if defined(LZO1X)
				*op++ = LZO_BYTE(((m_len - 1) << 5) | ((m_off & 7) << 2));
				*op++ = LZO_BYTE(m_off >> 3);
#elif defined(LZO1Y)
				*op++ = LZO_BYTE(((m_len + 1) << 4) | ((m_off & 3) << 2));
				*op++ = LZO_BYTE(m_off >> 2);
#endif
			}
			else if (m_off <= M3_MAX_OFFSET)
			{
				m_off -= 1;
				*op++ = LZO_BYTE(M3_MARKER | (m_len - 2));
				goto m3_m4_offset;
			}
			else
#if defined(LZO1X)
			{
				m_off -= 0x4000;
				assert(m_off > 0); assert(m_off <= 0x7fff);
				*op++ = LZO_BYTE(M4_MARKER |
								 ((m_off & 0x4000) >> 11) | (m_len - 2));
				goto m3_m4_offset;
			}
#elif defined(LZO1Y)
				goto m4_match;
#endif
		}
		else
		{
			{
				const lzo_bytep end = in_end;
				const lzo_bytep m = m_pos + M2_MAX_LEN + 1;
				while (ip < end && *m == *ip)
					m++, ip++;
				m_len = pd(ip, ii);
			}
			assert(m_len > M2_MAX_LEN);

			if (m_off <= M3_MAX_OFFSET)
			{
				m_off -= 1;
				if (m_len <= 33)
					*op++ = LZO_BYTE(M3_MARKER | (m_len - 2));
				else
				{
					m_len -= 33;
					*op++ = M3_MARKER | 0;
					goto m3_m4_len;
				}
			}
			else
			{
#if defined(LZO1Y)
m4_match:
#endif
				m_off -= 0x4000;
				assert(m_off > 0); assert(m_off <= 0x7fff);
				if (m_len <= M4_MAX_LEN)
					*op++ = LZO_BYTE(M4_MARKER |
									 ((m_off & 0x4000) >> 11) | (m_len - 2));
				else
				{
					m_len -= M4_MAX_LEN;
					*op++ = LZO_BYTE(M4_MARKER | ((m_off & 0x4000) >> 11));
m3_m4_len:
					while (m_len > 255)
					{
						m_len -= 255;
						*op++ = 0;
					}
					assert(m_len > 0);
					*op++ = LZO_BYTE(m_len);
				}
			}

m3_m4_offset:
			*op++ = LZO_BYTE((m_off & 63) << 2);
			*op++ = LZO_BYTE(m_off >> 6);
		}
