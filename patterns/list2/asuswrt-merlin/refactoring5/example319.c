# ifndef OPENSSL_NO_DSA
if (dsaparam) {
        if (g) {
            BIO_printf(bio_err,
                       "generator may not be chosen for DSA parameters\n");
            goto end;
        }
    } else
# endif
    {
        /* DH parameters */
        if (num && !g)
            g = 2;
    }
