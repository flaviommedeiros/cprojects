xim_externaldef XimFrameRec str_conversion_fr[] = {
    _FRAME(BIT16),      /* input-method-ID */
    _FRAME(BIT16),      /* input-context-ID */
    _FRAME(BIT32),      /* XIMStringConversionPosition */
    _FRAME(BIT32),      /* XIMStringConversionType */
    _FRAME(BIT32),      /* XIMStringConversionOperation */
    _FRAME(BIT16),      /* length to multiply the
                       XIMStringConversionType */
    _FRAME(BIT16),      /* length of the string to be
                       substituted */
#if 0
    _FRAME(BARRAY),         /* string */
    _PAD4(1),
#endif
    _FRAME(EOL),
};
