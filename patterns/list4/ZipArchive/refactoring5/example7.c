#ifndef NOUNCRYPT
if ((s->cur_file_info.flag & 1) != 0) {
#ifdef HAVE_AES
                if (s->cur_file_info.compression_method == AES_METHOD) {
                    fcrypt_decrypt(pfile_in_zip_read_info->read_buffer, bytes_to_read, &s->pfile_in_zip_read->aes_ctx);
                } else
#endif
                {
                    uInt i;
                    for (i = 0; i < total_bytes_read; i++)
                        pfile_in_zip_read_info->read_buffer[i] =
                            zdecode(s->keys, s->pcrc_32_tab, pfile_in_zip_read_info->read_buffer[i]);
                }
            }
