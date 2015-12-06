switch (self->mode) {
        case ZARMOUR_MODE_BASE64_STD:
            encoded = s_base64_encode (data, data_size, s_base64_alphabet, self->pad, self->pad_char);
            break;
        case ZARMOUR_MODE_BASE64_URL:
            encoded = s_base64_encode (data, data_size, s_base64url_alphabet, self->pad, self->pad_char);
            break;
        case ZARMOUR_MODE_BASE32_STD:
            encoded = s_base32_encode (data, data_size, s_base32_alphabet, self->pad, self->pad_char);
            break;
        case ZARMOUR_MODE_BASE32_HEX:
            encoded = s_base32_encode (data, data_size, s_base32hex_alphabet, self->pad, self->pad_char);
            break;
        case ZARMOUR_MODE_BASE16:
            encoded = s_base16_encode (data, data_size, s_base16_alphabet);
            break;
#ifdef _INCLUDE_Z85
        case ZARMOUR_MODE_Z85:
            encoded = s_z85_encode (data, data_size);
            break;
#endif
    }
