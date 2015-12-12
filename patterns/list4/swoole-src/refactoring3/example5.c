switch(type)
    {
#ifdef HAVE_RWLOCK
    case SW_RWLOCK:
        ret = swRWLock_create(lock, 1);
        break;
#endif
    case SW_FILELOCK:
        if (filelock_len <= 0)
        {
            php_error_docref(NULL TSRMLS_CC, E_ERROR, "filelock require lock file name.");
            RETURN_FALSE;
        }
        int fd;
        if ((fd = open(filelock, O_RDWR | O_CREAT, 0666)) < 0)
        {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "open file[%s] failed. Error: %s [%d]", filelock, strerror(errno), errno);
            RETURN_FALSE;
        }
        ret = swFileLock_create(lock, fd);
        break;
    case SW_SEM:
        ret = swSem_create(lock, IPC_PRIVATE);
        break;
#ifdef HAVE_SPINLOCK
    case SW_SPINLOCK:
        ret = swSpinLock_create(lock, 1);
        break;
#endif
    case SW_MUTEX:
    default:
        ret = swMutex_create(lock, 1);
        break;
    }
