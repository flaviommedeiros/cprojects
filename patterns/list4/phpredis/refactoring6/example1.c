if(val_long == REDIS_SERIALIZER_NONE
#ifdef HAVE_REDIS_IGBINARY
                || val_long == REDIS_SERIALIZER_IGBINARY
#endif
                || val_long == REDIS_SERIALIZER_PHP)
                {
                    redis_sock->serializer = val_long;
                    RETURN_TRUE;
                } else {
                    RETURN_FALSE;
                }
