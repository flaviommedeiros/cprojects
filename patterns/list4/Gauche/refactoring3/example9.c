switch (saddr->sa_family) {
        case AF_UNIX:
            klass = SCM_CLASS_SOCKADDR_UN;
            break;
        case AF_INET:
            klass = SCM_CLASS_SOCKADDR_IN;
            break;
#ifdef HAVE_IPV6
        case AF_INET6:
            klass = SCM_CLASS_SOCKADDR_IN6;
            break;
#endif
        default:
            Scm_Error("unknown address family (%d)", saddr->sa_family);
            break;
        }
