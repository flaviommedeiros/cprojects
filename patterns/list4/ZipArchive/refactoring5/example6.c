#ifdef HAVE_AES
if (s->cur_file_info.compression_method == AES_METHOD) {
            unsigned char passverify[AES_PWVERIFYSIZE];
            unsigned char saltvalue[AES_MAXSALTLENGTH];
            uInt saltlength;

            if ((s->cur_file_info_internal.aes_encryption_mode < 1) ||
                (s->cur_file_info_internal.aes_encryption_mode > 3))
                return UNZ_INTERNALERROR;

            saltlength = SALT_LENGTH(s->cur_file_info_internal.aes_encryption_mode);

            if (ZREAD64(s->z_filefunc, s->filestream, saltvalue, saltlength) != saltlength)
                return UNZ_INTERNALERROR;
            if (ZREAD64(s->z_filefunc, s->filestream, passverify, AES_PWVERIFYSIZE) != AES_PWVERIFYSIZE)
                return UNZ_INTERNALERROR;

            fcrypt_init((int)s->cur_file_info_internal.aes_encryption_mode, (unsigned char *)password, (unsigned int)strlen(password), saltvalue,
                        passverify, &s->pfile_in_zip_read->aes_ctx);

            pfile_in_zip_read_info->rest_read_compressed -= saltlength + AES_PWVERIFYSIZE;
            pfile_in_zip_read_info->rest_read_compressed -= AES_AUTHCODESIZE;

            s->pfile_in_zip_read->pos_in_zipfile += saltlength + AES_PWVERIFYSIZE;
        } else
#endif
        {
            int i;
            s->pcrc_32_tab = (const unsigned long *)get_crc_table();
            init_keys(password, s->keys, s->pcrc_32_tab);

            if (ZREAD64(s->z_filefunc, s->filestream, source, 12) < 12)
                return UNZ_INTERNALERROR;

            for (i = 0; i < 12; i++)
                zdecode(s->keys, s->pcrc_32_tab, source[i]);

            pfile_in_zip_read_info->rest_read_compressed -= 12;

            s->pfile_in_zip_read->pos_in_zipfile += 12;
        }
