if (((obits & PCRE_NEWLINE_BITS) == PCRE_NEWLINE_ANY ||
               (obits & PCRE_NEWLINE_BITS) == PCRE_NEWLINE_CRLF ||
               (obits & PCRE_NEWLINE_BITS) == PCRE_NEWLINE_ANYCRLF)
              &&
              start_offset < len - 1 &&
#if defined SUPPORT_PCRE8 && defined SUPPORT_PCRE16
              (use_pcre16?
                   ((PCRE_SPTR16)bptr)[start_offset] == '\r'
                && ((PCRE_SPTR16)bptr)[start_offset + 1] == '\n'
              :
                   bptr[start_offset] == '\r'
                && bptr[start_offset + 1] == '\n')
#elif defined SUPPORT_PCRE16
                 ((PCRE_SPTR16)bptr)[start_offset] == '\r'
              && ((PCRE_SPTR16)bptr)[start_offset + 1] == '\n'
#else
                 bptr[start_offset] == '\r'
              && bptr[start_offset + 1] == '\n'
#endif
              )
            onechar++;
          else if (use_utf)
            {
            while (start_offset + onechar < len)
              {
              if ((bptr[start_offset+onechar] & 0xc0) != 0x80) break;
              onechar++;
              }
            }
