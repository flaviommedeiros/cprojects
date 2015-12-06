return n == 0 || (n < 0 && errno != EINTR && errno != EINPROGRESS &&
                    errno != EAGAIN && errno != EWOULDBLOCK
#ifdef NS_CC3200
                    && errno != SL_EALREADY
#endif
#ifdef _WIN32
                    && WSAGetLastError() != WSAEINTR &&
                    WSAGetLastError() != WSAEWOULDBLOCK
#endif
                    );
