switch (nid) {
# ifdef USE_CRYPTODEV_DIGESTS
    case NID_md5:
        *digest = &cryptodev_md5;
        break;
    case NID_sha1:
        *digest = &cryptodev_sha1;
        break;
    default:
# endif                         /* USE_CRYPTODEV_DIGESTS */
        *digest = NULL;
        break;
    }
