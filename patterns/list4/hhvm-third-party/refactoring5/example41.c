#ifdef SUPPORT_UTF
if (common->utf)
      {
      GETCHAR(chr, cc);
      if ((int)PRIV(ord2utf)(char_othercase(common, chr), othercase) != len)
        return consumed;
      }
    else
#endif
      {
      chr = *cc;
      othercase[0] = TABLE_GET(chr, common->fcc, chr);
      }
