if (((obits & PCRE_NEWLINE_BITS) == PCRE_NEWLINE_ANY ||
               (obits & PCRE_NEWLINE_BITS) == PCRE_NEWLINE_CRLF ||
               (obits & PCRE_NEWLINE_BITS) == PCRE_NEWLINE_ANYCRLF)
              &&
              start_offset < len - 1 && (
#ifdef SUPPORT_PCRE8
              (pcre_mode == PCRE8_MODE &&
               bptr[start_offset] == '\r' &&
               bptr[start_offset + 1] == '\n') ||
#endif
#ifdef SUPPORT_PCRE16
              (pcre_mode == PCRE16_MODE &&
               ((PCRE_SPTR16)bptr)[start_offset] == '\r' &&
               ((PCRE_SPTR16)bptr)[start_offset + 1] == '\n') ||
#endif
#ifdef SUPPORT_PCRE32
              (pcre_mode == PCRE32_MODE &&
               ((PCRE_SPTR32)bptr)[start_offset] == '\r' &&
               ((PCRE_SPTR32)bptr)[start_offset + 1] == '\n') ||
#endif
              0))
            onechar++;
          else if (use_utf)
            {
            while (start_offset + onechar < len)
              {
              if ((bptr[start_offset+onechar] & 0xc0) != 0x80) break;
              onechar++;
              }
            }
