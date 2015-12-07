if ( m_len < 2 ||
            (m_len == 2 && (m_off > M1_MAX_OFFSET || lit == 0 || lit >= 4)) ||
#if 1
            /* Do not accept this match for compressed-data compatibility
             * with LZO v1.01 and before
             * [ might be a problem for decompress() and optimize() ]
             */
            (m_len == 2 && op == out) ||
#endif
            (op == out && lit == 0))
        {
            /* a literal */
            m_len = 0;
        }
        else if (m_len == M2_MIN_LEN)
        {
            /* compression ratio improves if we code a literal in some cases */
            if (m_off > MX_MAX_OFFSET && lit >= 4)
                m_len = 0;
        }
