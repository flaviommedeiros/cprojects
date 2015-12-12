#ifdef HAVE_AES
if (zi->ci.method == AES_METHOD) {
            unsigned char passverify[AES_PWVERIFYSIZE];
            unsigned char saltvalue[AES_MAXSALTLENGTH];
            uInt saltlength;

            if ((AES_ENCRYPTIONMODE < 1) || (AES_ENCRYPTIONMODE > 3))
                return Z_ERRNO;

            saltlength = SALT_LENGTH(AES_ENCRYPTIONMODE);

            prng_init(entropy_fun, zi->ci.aes_rng);
            prng_rand(saltvalue, saltlength, zi->ci.aes_rng);
            prng_end(zi->ci.aes_rng);

            fcrypt_init(AES_ENCRYPTIONMODE, (unsigned char *)password, (unsigned int)strlen(password), saltvalue, passverify, &zi->ci.aes_ctx);

            if (ZWRITE64(zi->z_filefunc, zi->filestream, saltvalue, saltlength) != saltlength)
                err = ZIP_ERRNO;
            if (ZWRITE64(zi->z_filefunc, zi->filestream, passverify, AES_PWVERIFYSIZE) != AES_PWVERIFYSIZE)
                err = ZIP_ERRNO;

            zi->ci.crypt_header_size = saltlength + AES_PWVERIFYSIZE + AES_AUTHCODESIZE;
        } else
#endif
        {
            unsigned char bufHead[RAND_HEAD_LEN];
            unsigned int sizeHead;

            zi->ci.pcrc_32_tab = (const unsigned long *)get_crc_table();
            /*init_keys(password, zi->ci.keys, zi->ci.pcrc_32_tab);*/

            sizeHead = crypthead(password, bufHead, RAND_HEAD_LEN, zi->ci.keys, zi->ci.pcrc_32_tab, crcForCrypting);
            zi->ci.crypt_header_size = sizeHead;

            if (ZWRITE64(zi->z_filefunc, zi->filestream, bufHead, sizeHead) != sizeHead)
                err = ZIP_ERRNO;
        }
