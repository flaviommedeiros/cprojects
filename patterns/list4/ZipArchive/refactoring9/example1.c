int fcrypt_init(
    int mode,                               /* the mode to be used (input)          */
    const unsigned char pwd[],              /* the user specified password (input)  */
    unsigned int pwd_len,                   /* the length of the password (input)   */
    const unsigned char salt[],             /* the salt (input)                     */
#ifdef PASSWORD_VERIFIER
    unsigned char pwd_ver[PWD_VER_LENGTH],  /* 2 byte password verifier (output)    */
#endif
    fcrypt_ctx cx[1])                       /* the file encryption context (output) */
{
    unsigned char kbuf[2 * MAX_KEY_LENGTH + PWD_VER_LENGTH];

    if (pwd_len > MAX_PWD_LENGTH)
        return PASSWORD_TOO_LONG;

    if (mode < 1 || mode > 3)
        return BAD_MODE;

    cx->mode = mode;
    cx->pwd_len = pwd_len;

    /* derive the encryption and authentication keys and the password verifier   */
    derive_key(pwd, pwd_len, salt, SALT_LENGTH(mode), KEYING_ITERATIONS,
               kbuf, 2 * KEY_LENGTH(mode) + PWD_VER_LENGTH);

    /* initialise the encryption nonce and buffer pos   */
    cx->encr_pos = AES_BLOCK_SIZE;
    /* if we need a random component in the encryption  */
    /* nonce, this is where it would have to be set     */
    memset(cx->nonce, 0, AES_BLOCK_SIZE * sizeof(unsigned char));

    /* initialise for encryption using key 1            */
    aes_encrypt_key(kbuf, KEY_LENGTH(mode), cx->encr_ctx);

    /* initialise for authentication using key 2        */
    hmac_sha_begin(cx->auth_ctx);
    hmac_sha_key(kbuf + KEY_LENGTH(mode), KEY_LENGTH(mode), cx->auth_ctx);

#ifdef PASSWORD_VERIFIER
    memcpy(pwd_ver, kbuf + 2 * KEY_LENGTH(mode), PWD_VER_LENGTH);
#endif

    return GOOD_RETURN;
}
