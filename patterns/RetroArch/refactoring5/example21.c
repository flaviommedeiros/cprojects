#ifdef GZIP
if (s->wrap == 2) {
         strm->adler = crc32(0L, Z_NULL, 0);
         put_byte(s, 31);
         put_byte(s, 139);
         put_byte(s, 8);
         if (s->gzhead == Z_NULL) {
            put_byte(s, 0);
            put_byte(s, 0);
            put_byte(s, 0);
            put_byte(s, 0);
            put_byte(s, 0);
            put_byte(s, s->level == 9 ? 2 :
                  (s->strategy >= Z_HUFFMAN_ONLY || s->level < 2 ?
                   4 : 0));
            put_byte(s, OS_CODE);
            s->status = BUSY_STATE;
         }
         else {
            put_byte(s, (s->gzhead->text ? 1 : 0) +
                  (s->gzhead->hcrc ? 2 : 0) +
                  (s->gzhead->extra == Z_NULL ? 0 : 4) +
                  (s->gzhead->name == Z_NULL ? 0 : 8) +
                  (s->gzhead->comment == Z_NULL ? 0 : 16)
                  );
            put_byte(s, (Byte)(s->gzhead->time & 0xff));
            put_byte(s, (Byte)((s->gzhead->time >> 8) & 0xff));
            put_byte(s, (Byte)((s->gzhead->time >> 16) & 0xff));
            put_byte(s, (Byte)((s->gzhead->time >> 24) & 0xff));
            put_byte(s, s->level == 9 ? 2 :
                  (s->strategy >= Z_HUFFMAN_ONLY || s->level < 2 ?
                   4 : 0));
            put_byte(s, s->gzhead->os & 0xff);
            if (s->gzhead->extra != Z_NULL) {
               put_byte(s, s->gzhead->extra_len & 0xff);
               put_byte(s, (s->gzhead->extra_len >> 8) & 0xff);
            }
            if (s->gzhead->hcrc)
               strm->adler = crc32(strm->adler, s->pending_buf,
                     s->pending);
            s->gzindex = 0;
            s->status = EXTRA_STATE;
         }
      }
      else
#endif
      {
         uInt header = (Z_DEFLATED + ((s->w_bits-8)<<4)) << 8;
         uInt level_flags;

         if (s->strategy >= Z_HUFFMAN_ONLY || s->level < 2)
            level_flags = 0;
         else if (s->level < 6)
            level_flags = 1;
         else if (s->level == 6)
            level_flags = 2;
         else
            level_flags = 3;
         header |= (level_flags << 6);
         if (s->strstart != 0) header |= PRESET_DICT;
         header += 31 - (header % 31);

         s->status = BUSY_STATE;
         putShortMSB(s, header);

         /* Save the adler32 of the preset dictionary: */
         if (s->strstart != 0) {
            putShortMSB(s, (uInt)(strm->adler >> 16));
            putShortMSB(s, (uInt)(strm->adler & 0xffff));
         }
         strm->adler = adler32(0L, Z_NULL, 0);
      }
