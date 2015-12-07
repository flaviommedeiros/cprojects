#ifdef TRY_URANDOM_FIRST
if (f == NULL)
#endif /* TRY_URANDOM_FIRST */
       f = fopen("/dev/random", "rb");
