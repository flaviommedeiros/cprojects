#if (LBITS < 8)
if (PS || PS)
#elif (MIN_MATCH_LONG - MIN_MATCH == 6)                 /* MBITS == 3 */
            if (PS || PS || PS || PS || PS || PS)
#elif (MIN_MATCH_LONG - MIN_MATCH == 14)                /* MBITS == 4 */
            if (PS || PS || PS || PS || PS || PS || PS ||
                PS || PS || PS || PS || PS || PS || PS)
#elif (MIN_MATCH_LONG - MIN_MATCH == 30)                /* MBITS == 5 */
            if (PS || PS || PS || PS || PS || PS || PS || PS ||
                PS || PS || PS || PS || PS || PS || PS || PS ||
                PS || PS || PS || PS || PS || PS || PS || PS ||
                PS || PS || PS || PS || PS || PS)
#else
#  error "MBITS not yet implemented"
#endif
            {
            /* we've found a short match */
                lzo_uint m_len;

            /* 2a) compute match parameters */
                    assert(ip-m_pos == (int)m_off);
                --ip;   /* ran one too far, point back to non-match */
                m_len = pd(ip, ii);
                    assert(m_len >= MIN_MATCH_SHORT);
                    assert(m_len <= MAX_MATCH_SHORT);
                    assert(m_off >= MIN_OFFSET);
                    assert(m_off <= MAX_OFFSET);
                    assert(ii-m_off == m_pos_sav);
                    assert(lzo_memcmp(m_pos_sav,ii,m_len) == 0);
                m_off -= MIN_OFFSET;

            /* 2b) code a short match */
                /* code short match len + low offset bits */
                *op++ = LZO_BYTE(((m_len - THRESHOLD) << OBITS) |
                                 (m_off & OMASK));
                /* code high offset bits */
                *op++ = LZO_BYTE(m_off >> OBITS);


#if (LZO_COLLECT_STATS)
                lzo_stats->short_matches++;
                lzo_stats->short_match[m_len]++;
                if (m_off < OSIZE)
                    lzo_stats->short_match_offset_osize[m_len]++;
                if (m_off < 256)
                    lzo_stats->short_match_offset_256[m_len]++;
                if (m_off < 1024)
                    lzo_stats->short_match_offset_1024[m_len]++;
#endif


            /* 2c) Insert phrases (beginning with ii+1) into the dictionary. */

#define SI      /* nothing */
#define DI      ++ii; DVAL_NEXT(dv,ii); UPDATE_D(dict,0,dv,ii,in);
#define XI      assert(ii < ip); ii = ip; DVAL_FIRST(dv,(ip));

#if (CLEVEL == 9) || (CLEVEL >= 7 && MBITS <= 4) || (CLEVEL >= 5 && MBITS <= 3)
            /* Insert the whole match (ii+1)..(ip-1) into dictionary.  */
                ++ii;
                do {
                    DVAL_NEXT(dv,ii);
                    UPDATE_D(dict,0,dv,ii,in);
                } while (++ii < ip);
                DVAL_NEXT(dv,ii);
                assert(ii == ip);
                DVAL_ASSERT(dv,ip);
#elif (CLEVEL >= 3)
                SI   DI DI   XI
#elif (CLEVEL >= 2)
                SI   DI      XI
#else
                             XI
#endif

            }
            else
            {
            /* we've found a long match - see how far we can still go */
                const lzo_bytep end;
                lzo_uint m_len;

                assert(ip <= in_end);
                assert(ii == ip - MIN_MATCH_LONG);

                if (pd(in_end,ip) <= (MAX_MATCH_LONG - MIN_MATCH_LONG))
                    end = in_end;
                else
                {
                    end = ip + (MAX_MATCH_LONG - MIN_MATCH_LONG);
                    assert(end < in_end);
                }

                while (ip < end  &&  *m_pos == *ip)
                    m_pos++, ip++;
                assert(ip <= in_end);

            /* 2a) compute match parameters */
                m_len = pd(ip, ii);
                    assert(m_len >= MIN_MATCH_LONG);
                    assert(m_len <= MAX_MATCH_LONG);
                    assert(m_off >= MIN_OFFSET);
                    assert(m_off <= MAX_OFFSET);
                    assert(ii-m_off == m_pos_sav);
                    assert(lzo_memcmp(m_pos_sav,ii,m_len) == 0);
                    assert(pd(ip,m_pos) == m_off);
                m_off -= MIN_OFFSET;

            /* 2b) code the long match */
                /* code long match flag + low offset bits */
                *op++ = LZO_BYTE(((MSIZE - 1) << OBITS) | (m_off & OMASK));
                /* code high offset bits */
                *op++ = LZO_BYTE(m_off >> OBITS);
                /* code match len */
                *op++ = LZO_BYTE(m_len - MIN_MATCH_LONG);


#if (LZO_COLLECT_STATS)
                lzo_stats->long_matches++;
                lzo_stats->long_match[m_len]++;
#endif


            /* 2c) Insert phrases (beginning with ii+1) into the dictionary. */
#if (CLEVEL == 9)
            /* Insert the whole match (ii+1)..(ip-1) into dictionary.  */
            /* This is not recommended because it is slow. */
                ++ii;
                do {
                    DVAL_NEXT(dv,ii);
                    UPDATE_D(dict,0,dv,ii,in);
                } while (++ii < ip);
                DVAL_NEXT(dv,ii);
                assert(ii == ip);
                DVAL_ASSERT(dv,ip);
#elif (CLEVEL >= 8)
                SI   DI DI DI DI DI DI DI DI   XI
#elif (CLEVEL >= 7)
                SI   DI DI DI DI DI DI DI      XI
#elif (CLEVEL >= 6)
                SI   DI DI DI DI DI DI         XI
#elif (CLEVEL >= 5)
                SI   DI DI DI DI               XI
#elif (CLEVEL >= 4)
                SI   DI DI DI                  XI
#elif (CLEVEL >= 3)
                SI   DI DI                     XI
#elif (CLEVEL >= 2)
                SI   DI                        XI
#else
                                               XI
#endif
            }
