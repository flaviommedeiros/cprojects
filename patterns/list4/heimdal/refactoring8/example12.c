static struct hx509_private_key_ops *private_algs[] = {
    &rsa_private_key_ops,
#ifdef HAVE_OPENSSL
    &ecdsa_private_key_ops,
#endif
    NULL
};
