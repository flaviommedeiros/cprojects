#if !PJ_ANDROID
if( !wait )
        pthread_cancel( threading->callbackThread );
