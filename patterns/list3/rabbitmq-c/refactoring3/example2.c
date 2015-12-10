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
        ret = AMQP_PRIVATE_STATUS_SOCKET_NEEDREAD;
        break;
      default:
        ret = AMQP_STATUS_SOCKET_ERROR;
    }
