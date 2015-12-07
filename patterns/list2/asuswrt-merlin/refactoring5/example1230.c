#ifdef ENABLE_CRYPTO
if (options->test_crypto)
    {
      notnull (options->shared_secret_file, "key file (--secret)");
    }
  else
#endif
    notnull (options->dev, "TUN/TAP device (--dev)");
