#ifdef SUPPORT_UTF
if (utf && (c & UTF_LENGTH) != 0)
            {
            memcpy(code, utf_chars, IN_UCHARS(c & 7));
            code += c & 7;
            }
          else
#endif
            {
            *code++ = c;
            if (prop_type >= 0)
              {
              *code++ = prop_type;
              *code++ = prop_value;
              }
            }
