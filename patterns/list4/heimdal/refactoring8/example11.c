static const struct signature_alg *sig_algs[] = {
#ifdef HAVE_OPENSSL
    &ecdsa_with_sha256_alg,
    &ecdsa_with_sha1_alg,
#endif
    &rsa_with_sha512_alg,
    &rsa_with_sha384_alg,
    &rsa_with_sha256_alg,
    &rsa_with_sha1_alg,
    &rsa_with_sha1_alg_secsig,
    &pkcs1_rsa_sha1_alg,
    &rsa_with_md5_alg,
    &heim_rsa_pkcs1_x509,
    &dsa_sha1_alg,
    &sha512_alg,
    &sha384_alg,
    &sha256_alg,
    &sha1_alg,
    &md5_alg,
    NULL
};
