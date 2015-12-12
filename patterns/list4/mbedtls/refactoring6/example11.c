if(
#if defined(MBEDTLS_MEMORY_DEBUG)
        heap.total_used != 0 ||
#endif
        heap.first != heap.first_free ||
        (void *) heap.first != (void *) heap.buf )
    {
        return( -1 );
    }
