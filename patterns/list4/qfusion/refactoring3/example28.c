switch (EVP_MD_CTX_type(ctx)) {
    case NID_md5:
    case NID_sha1:
#ifndef OPENSSL_NO_SHA256
    case NID_sha224:
    case NID_sha256:
#endif
#ifndef OPENSSL_NO_SHA512
    case NID_sha384:
    case NID_sha512:
#endif
        return 1;
    default:
        return 0;
    }
