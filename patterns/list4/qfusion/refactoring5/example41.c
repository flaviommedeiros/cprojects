# ifndef OPENSSL_NO_DSA
if (dsaparam) {
            DSA *dsa;

            if (informat == FORMAT_ASN1)
                dsa = d2i_DSAparams_bio(in, NULL);
            else                /* informat == FORMAT_PEM */
                dsa = PEM_read_bio_DSAparams(in, NULL, NULL, NULL);

            if (dsa == NULL) {
                BIO_printf(bio_err, "unable to load DSA parameters\n");
                ERR_print_errors(bio_err);
                goto end;
            }

            dh = DSA_dup_DH(dsa);
            DSA_free(dsa);
            if (dh == NULL) {
                ERR_print_errors(bio_err);
                goto end;
            }
        } else
# endif
        {
            if (informat == FORMAT_ASN1)
                dh = d2i_DHparams_bio(in, NULL);
            else                /* informat == FORMAT_PEM */
                dh = PEM_read_bio_DHparams(in, NULL, NULL, NULL);

            if (dh == NULL) {
                BIO_printf(bio_err, "unable to load DH parameters\n");
                ERR_print_errors(bio_err);
                goto end;
            }
        }
