switch (hashType) {
#ifndef NO_MD5
        case MD5:
            wc_InitMd5(&md5);
            wc_Md5Update(&md5, passwd, pLen);
            wc_Md5Update(&md5, salt,   sLen);
            wc_Md5Final(&md5,  buffer);
            break;
#endif /* NO_MD5 */
        case SHA:
        default:
            ret = wc_InitSha(&sha);
            if (ret != 0)
                return ret;
            wc_ShaUpdate(&sha, passwd, pLen);
            wc_ShaUpdate(&sha, salt,   sLen);
            wc_ShaFinal(&sha,  buffer);
            break;
    }
