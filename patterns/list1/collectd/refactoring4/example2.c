#if HAVE_LIBGCRYPT
if (!gcry_check_version (GCRYPT_VERSION))
    return (0);
