#ifdef PNG_iTXt_SUPPORTED
if (text_ptr[i].compression > 0)
      {
         textp->lang = textp->key + key_len + 1;
         png_memcpy(textp->lang, text_ptr[i].lang, lang_len);
         *(textp->lang + lang_len) = '\0';
         textp->lang_key = textp->lang + lang_len + 1;
         png_memcpy(textp->lang_key, text_ptr[i].lang_key, lang_key_len);
         *(textp->lang_key + lang_key_len) = '\0';
         textp->text = textp->lang_key + lang_key_len + 1;
      }
      else
#endif
      {
#ifdef PNG_iTXt_SUPPORTED
         textp->lang=NULL;
         textp->lang_key=NULL;
#endif
         textp->text = textp->key + key_len + 1;
      }
