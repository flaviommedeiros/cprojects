#if !PJ_ANDROID
if( pret && PTHREAD_CANCELED != pret )
#else
		       /* !wait means the thread may have been canceled */
		       if( pret && wait )
#endif

    {
        if( exitResult )
        {
            *exitResult = *(PaError*)pret;
        }
        free( pret );
    }
