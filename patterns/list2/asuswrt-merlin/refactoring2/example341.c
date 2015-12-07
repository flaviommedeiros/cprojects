#ifdef HAVE_SSL
if (u->scheme != SCHEME_HTTPS)
#endif
        request_set_header (req, "Proxy-Authorization", proxyauth, rel_value);
