#if defined(LZO1Z)
if (m_len <= M2_MAX_LEN && (m_off <= M2_MAX_OFFSET || m_off == c->last_m_off))
#else
    else if (m_len <= M2_MAX_LEN && m_off <= M2_MAX_OFFSET)
#endif
    {
        assert(m_len >= 3);
#if defined(LZO1X)
        m_off -= 1;
        *op++ = LZO_BYTE(((m_len - 1) << 5) | ((m_off & 7) << 2));
        *op++ = LZO_BYTE(m_off >> 3);
        assert(op[-2] >= M2_MARKER);
#elif defined(LZO1Y)
        m_off -= 1;
        *op++ = LZO_BYTE(((m_len + 1) << 4) | ((m_off & 3) << 2));
        *op++ = LZO_BYTE(m_off >> 2);
        assert(op[-2] >= M2_MARKER);
#elif defined(LZO1Z)
        if (m_off == c->last_m_off)
            *op++ = LZO_BYTE(((m_len - 1) << 5) | (0x700 >> 6));
        else
        {
            m_off -= 1;
            *op++ = LZO_BYTE(((m_len - 1) << 5) | (m_off >> 6));
            *op++ = LZO_BYTE(m_off << 2);
        }
#endif
        c->m2_m++;
    }
    else if (m_len == M2_MIN_LEN && m_off <= MX_MAX_OFFSET && c->r1_lit >= 4)
    {
        assert(m_len == 3);
        assert(m_off > M2_MAX_OFFSET);
        m_off -= 1 + M2_MAX_OFFSET;
#if defined(LZO1Z)
        *op++ = LZO_BYTE(M1_MARKER | (m_off >> 6));
        *op++ = LZO_BYTE(m_off << 2);
#else
        *op++ = LZO_BYTE(M1_MARKER | ((m_off & 3) << 2));
        *op++ = LZO_BYTE(m_off >> 2);
#endif
        c->m1b_m++;
    }
    else if (m_off <= M3_MAX_OFFSET)
    {
        assert(m_len >= 3);
        m_off -= 1;
        if (m_len <= M3_MAX_LEN)
            *op++ = LZO_BYTE(M3_MARKER | (m_len - 2));
        else
        {
            m_len -= M3_MAX_LEN;
            *op++ = M3_MARKER | 0;
            while (m_len > 255)
            {
                m_len -= 255;
                *op++ = 0;
            }
            assert(m_len > 0);
            *op++ = LZO_BYTE(m_len);
        }
#if defined(LZO1Z)
        *op++ = LZO_BYTE(m_off >> 6);
        *op++ = LZO_BYTE(m_off << 2);
#else
        *op++ = LZO_BYTE(m_off << 2);
        *op++ = LZO_BYTE(m_off >> 6);
#endif
        c->m3_m++;
    }
    else
    {
        lzo_uint k;

        assert(m_len >= 3);
        assert(m_off > 0x4000); assert(m_off <= 0xbfff);
        m_off -= 0x4000;
        k = (m_off & 0x4000) >> 11;
        if (m_len <= M4_MAX_LEN)
            *op++ = LZO_BYTE(M4_MARKER | k | (m_len - 2));
        else
        {
            m_len -= M4_MAX_LEN;
            *op++ = LZO_BYTE(M4_MARKER | k | 0);
            while (m_len > 255)
            {
                m_len -= 255;
                *op++ = 0;
            }
            assert(m_len > 0);
            *op++ = LZO_BYTE(m_len);
        }
#if defined(LZO1Z)
        *op++ = LZO_BYTE(m_off >> 6);
        *op++ = LZO_BYTE(m_off << 2);
#else
        *op++ = LZO_BYTE(m_off << 2);
        *op++ = LZO_BYTE(m_off >> 6);
#endif
        c->m4_m++;
    }
