if (c_tolower (*n) == c && pattern_match (p, n))
            return true;
#ifdef ASTERISK_EXCLUDES_DOT
          else if (*n == '.')
            return false;
#endif
