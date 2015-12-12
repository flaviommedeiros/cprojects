#ifdef __CYGWIN__
if ((errno == EAGAIN) || (errno == ECOMM))
#else
            if (errno == EAGAIN)
#endif /* __CYGWIN__ */
                return WEECHAT_RC_OK;
