switch (self->mode) {
        case ZARMOUR_MODE_BASE64_STD:
            return s_base64_decode (data, decode_size, s_base64_alphabet, linebreakchars);
        case ZARMOUR_MODE_BASE64_URL:
            return s_base64_decode (data, decode_size, s_base64url_alphabet, linebreakchars);
        case ZARMOUR_MODE_BASE32_STD:
            return s_base32_decode (data, decode_size, s_base32_alphabet, linebreakchars);
        case ZARMOUR_MODE_BASE32_HEX:
            return s_base32_decode (data, decode_size, s_base32hex_alphabet, linebreakchars);
        case ZARMOUR_MODE_BASE16:
            return s_base16_decode (data, decode_size, s_base16_alphabet, linebreakchars);
#ifdef _INCLUDE_Z85
        case ZARMOUR_MODE_Z85:
            return s_z85_decode (data, decode_size);
#endif
    }
