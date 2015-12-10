switch (self->internal_error) {
      case EINTR:
        goto start;
#ifdef _WIN32
      case WSAEWOULDBLOCK:
#else
      case EWOULDBLOCK:
#endif
#if defined(EAGAIN) && EAGAIN != EWOULDBLOCK
      case EAGAIN:
#endif
        res = AMQP_PRIVATE_STATUS_SOCKET_NEEDWRITE;
        break;
      default:
        res = AMQP_STATUS_SOCKET_ERROR;
    }
