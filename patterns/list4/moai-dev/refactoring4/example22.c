#if HAVE_ERRNO
if ( len < 0 && errno != EAGAIN )
#else
    if ( len < 0 )
#endif
    {
        perror( joy->os->fname );
        joy->error = 1;
    }
