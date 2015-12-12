switch (SwooleAIO.mode)
    {
#ifdef HAVE_LINUX_AIO
    case SW_AIO_LINUX:
        ret = swAioLinux_init(SW_AIO_EVENT_NUM);
        break;
#endif

#ifdef HAVE_GCC_AIO
    case SW_AIO_GCC:
        ret = swAioGcc_init(SW_AIO_EVENT_NUM);
        break;
#endif

    default:
        ret = swAioBase_init(SW_AIO_EVENT_NUM);
        break;
    }
