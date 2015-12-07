if ((c != NULL) && c->valid &&
#ifdef OPENSSL_FIPS
            (!FIPS_mode() || (c->algo_strength & SSL_FIPS)) &&
#endif
            !(c->algorithm_mkey & disabled_mkey) &&
            !(c->algorithm_auth & disabled_auth) &&
            !(c->algorithm_enc & disabled_enc) &&
            !(c->algorithm_mac & disabled_mac) &&
            !(c->algorithm_ssl & disabled_ssl)) {
            co_list[co_list_num].cipher = c;
            co_list[co_list_num].next = NULL;
            co_list[co_list_num].prev = NULL;
            co_list[co_list_num].active = 0;
            co_list_num++;
#ifdef KSSL_DEBUG
            fprintf(stderr, "\t%d: %s %lx %lx %lx\n", i, c->name, c->id,
                    c->algorithm_mkey, c->algorithm_auth);
#endif                          /* KSSL_DEBUG */
            /*
             * if (!sk_push(ca_list,(char *)c)) goto err;
             */
        }
