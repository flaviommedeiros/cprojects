___HIDDEN int tls_threading_cleanup
   ___PVOID
{
  int i;

  if (!tls_mutex_buf)
    return 0;

#if OPENSSL_VERSION_NUMBER < 0x10001000L
  CRYPTO_set_id_callback (NULL);
#elseif
  CRYPTO_THREADID_set_callback (NULL);
#endif
  CRYPTO_set_locking_callback (NULL);

  CRYPTO_set_dynlock_create_callback (NULL);
  CRYPTO_set_dynlock_lock_callback (NULL);
  CRYPTO_set_dynlock_destroy_callback (NULL);

  for (i = 0; i < CRYPTO_num_locks(); i++)
    ___MUTEX_DESTROY (tls_mutex_buf[i]);

  free (tls_mutex_buf);
  tls_mutex_buf = NULL;

  return 1;
}
