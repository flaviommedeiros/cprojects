#ifdef SW_HAVE_ZLIB
if (client->gzip_enable)
    {
        http_response_compress(&http_body, client->gzip_level);

        hex_string = swoole_dec2hex(swoole_zlib_buffer->length, 16);
        hex_len = strlen(hex_string);

        //"%*s\r\n%*s\r\n", hex_len, hex_string, body.length, body.str
        swString_append_ptr(swoole_http_buffer, hex_string, hex_len);
        swString_append_ptr(swoole_http_buffer, SW_STRL("\r\n") - 1);
        swString_append(swoole_http_buffer, swoole_zlib_buffer);
        swString_append_ptr(swoole_http_buffer, SW_STRL("\r\n") - 1);
    }
    else
#endif
    {
        hex_string = swoole_dec2hex(http_body.length, 16);
        hex_len = strlen(hex_string);

        //"%*s\r\n%*s\r\n", hex_len, hex_string, body.length, body.str
        swString_append_ptr(swoole_http_buffer, hex_string, hex_len);
        swString_append_ptr(swoole_http_buffer, SW_STRL("\r\n") - 1);
        swString_append_ptr(swoole_http_buffer, http_body.str, http_body.length);
        swString_append_ptr(swoole_http_buffer, SW_STRL("\r\n") - 1);
    }
