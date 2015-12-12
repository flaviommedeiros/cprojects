___HIDDEN int tls_threading_setup
   ___PVOID
{
  int i;
  tls_mutex_buf = (___MUTEX*)malloc (CRYPTO_num_locks() * sizeof(___MUTEX));

  if (!tls_mutex_buf)
    return 0;

  for (i = 0;  i < CRYPTO_num_locks();  i++)
    ___MUTEX_INIT (tls_mutex_buf[i]);

#if OPENSSL_VERSION_NUMBER < 0x10001000L
  CRYPTO_set_id_callback (tls_id_function);
#elseif
  CRYPTO_THREADID_set_callback (tls_id_function);
#endif
  CRYPTO_set_locking_callback (tls_locking_function);

  CRYPTO_set_dynlock_create_callback (tls_dyn_create_function);
  CRYPTO_set_dynlock_lock_callback (tls_dyn_lock_function);
  CRYPTO_set_dynlock_destroy_callback (tls_dyn_destroy_function);

  return 1;
}
