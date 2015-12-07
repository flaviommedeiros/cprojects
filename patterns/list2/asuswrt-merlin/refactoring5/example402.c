#ifdef REF_CHECK
if (pointer->references < 0) {
            fprintf(stderr,
                    "CRYPTO_destroy_dynlockid, bad reference count\n");
            abort();
        } else
#endif
        if (pointer->references <= 0) {
            (void)sk_CRYPTO_dynlock_set(dyn_locks, i, NULL);
        } else
            pointer = NULL;
