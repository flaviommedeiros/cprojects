#if defined(sgi) || ( defined(__osf__) && !defined(_CFE) )
if( listen(fd,1) <0 )   
#else
        if( listen(fd,0) <0 )   /* allow a queue of 0 */
#endif
        sockets_err("listen");
