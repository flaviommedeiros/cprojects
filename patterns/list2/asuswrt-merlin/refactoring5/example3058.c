#ifdef HAVE_STRUCT_SSL_METHOD_ST_GET_CIPHER_BY_CHAR
if (m && m->get_cipher_by_char) {
    unsigned char cipherid[3];
    set_uint16(cipherid, htons(cipher));
    cipherid[2] = 0; /* If ssl23_get_cipher_by_char finds no cipher starting
                      * with a two-byte 'cipherid', it may look for a v2
                      * cipher with the appropriate 3 bytes. */
    c = m->get_cipher_by_char(cipherid);
    if (c)
      tor_assert((c->id & 0xffff) == cipher);
    return c != NULL;
  } else
#endif
  if (m && m->get_cipher && m->num_ciphers) {
    /* It would seem that some of the "let's-clean-up-openssl" forks have
     * removed the get_cipher_by_char function.  Okay, so now you get a
     * quadratic search.
     */
    int i;
    for (i = 0; i < m->num_ciphers(); ++i) {
      c = m->get_cipher(i);
      if (c && (c->id & 0xffff) == cipher) {
        return 1;
      }
    }
    return 0;
  } else {
    return 1; /* No way to search */
  }
