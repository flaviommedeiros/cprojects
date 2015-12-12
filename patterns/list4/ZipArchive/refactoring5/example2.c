#ifdef HAVE_AES
if (zi->ci.method == AES_METHOD) {
            fcrypt_encrypt(zi->ci.buffered_data, zi->ci.pos_in_buffered_data, &zi->ci.aes_ctx);
        } else
#endif
        {
            uInt i;
            int t;
            for (i = 0; i < zi->ci.pos_in_buffered_data; i++)
                zi->ci.buffered_data[i] = zencode(zi->ci.keys, zi->ci.pcrc_32_tab, zi->ci.buffered_data[i], t);
        }
