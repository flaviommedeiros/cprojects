#ifdef WIN32
if (GetLastError() != WSAEWOULDBLOCK)
#else
            if (errno != EAGAIN && errno != EWOULDBLOCK)
#endif
                return SSL_ERROR_CONN_LOST;
