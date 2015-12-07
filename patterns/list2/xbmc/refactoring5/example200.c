#ifdef SUPPORT_UTF8
if (utf8 && class_lastchar > 127)
        mclength = _pcre_ord2utf8(class_lastchar, mcbuffer);
      else
#endif
        {
        mcbuffer[0] = class_lastchar;
        mclength = 1;
        }
